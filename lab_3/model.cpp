#include <random>
#include <map>
#include <iostream>
#include <QTime>
#include <QCoreApplication>
#include "model.h"

Model::Model(): level_(0), score_(0), pill_(Pill()), next_pill_(Pill()),
    game_field_matrix_(GameFieldTable(22,std::vector<CellState>(12, CellState::kEmpty))){
    InitializeGameField();
    GenerateViruses(level_);
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Model::PillMoveDownByTime);
    timer->start(1000);
}

void Model::GenerateViruses(int level){
    static std::map<int, CellState> viruses = {{0, CellState::kYellowVirus},
                                               {1, CellState::kBlueVirus},
                                               {2, CellState::kRedVirus}};
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    viruses_count_ = (rng()%8+2+level)%50;
    for(int i = 0; i < viruses_count_; i++){
        int virus_place = rng()%160+40;
        while(game_field_matrix_[virus_place/10+1][virus_place%10+1] != CellState::kEmpty){
            virus_place = rng()%160+40;
        }
        game_field_matrix_[virus_place/10+1][virus_place%10+1] = viruses[rng()%3];
    }
}

void Model::UpdateGameFieldChanges(){
    std::vector<Cell> game_field_cells;
    for(int i = 1; i < game_field_matrix_.size()-1; i++){
        for(int j = 1; j < game_field_matrix_[0].size()-1; j++){
            switch(game_field_matrix_[i][j]){
            case CellState::kRedPill:
                game_field_cells.push_back({j, i, Qt::red, Qt::SolidPattern});
                break;
            case CellState::kBluePill:
                game_field_cells.push_back({j, i, Qt::blue, Qt::SolidPattern});
                break;
            case CellState::kYellowPill:
                game_field_cells.push_back({j, i, Qt::yellow, Qt::SolidPattern});
                break;
            case CellState::kRedVirus:
                game_field_cells.push_back({j, i, Qt::red, Qt::Dense6Pattern});
                break;
            case CellState::kBlueVirus:
                game_field_cells.push_back({j, i, Qt::blue, Qt::Dense6Pattern});
                break;
            case CellState::kYellowVirus:
                game_field_cells.push_back({j, i, Qt::yellow, Qt::Dense6Pattern});
                break;
            case CellState::kOutOfBound:
                throw std::runtime_error("wrong game field matrix format");
                break;
            case CellState::kEmpty:
                game_field_cells.push_back({j, i, Qt::black, Qt::SolidPattern});
            }
        }
    }
    emit GameFieldChanged(game_field_cells, game_field_matrix_.size(), game_field_matrix_[0].size());
    emit ScoreChanged(score_);
}

void Model::StartSignalGot(){
    emit NextPillChanged(next_pill_.ConvertSelf());
    UpdateGameFieldChanges();
}

bool Model::PillMoved(MoveDirection direction){
    if(pill_.is_locked) return true;
    bool move_is_done = pill_.ProcessSelfMove(game_field_matrix_, direction);
    UpdateGameFieldChanges();
    return move_is_done;
}

//https://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
void Model::Delay(){
    QTime die_time = QTime::currentTime().addMSecs(250);
    while (QTime::currentTime() < die_time)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
}

void Model::PillMoveDownByTime(){
    if(!PillMoved(MoveDirection::kDown)){
        std::vector<std::vector<CellHangingState>> binding_states(game_field_matrix_.size(),
                            std::vector<CellHangingState>(game_field_matrix_[0].size(), CellHangingState::kEnshrined));
        while(1){
            if(!RemoveSequences(binding_states)) break;
            pill_.is_locked = true;
            emit ChangeActivationOfGameField(ModelActivationState::kDeactivate);
            std::vector<Figure> figures_to_drop = MakeHangingFigures(binding_states);
            while(figures_to_drop.size() > 0){
                DropFigures(figures_to_drop);
                UpdateGameFieldChanges();
                Delay();
            }
        }
        emit ChangeActivationOfGameField(ModelActivationState::kActivate);
        if(viruses_count_ == 0) ChangeLevel();
        else if(CheckPillAddPossibility()){
            ChangePill();
        }
        else {
            QCoreApplication::quit();
        }
    }
}

Figure Model::CreateFigureToDrop(std::vector<std::vector<CellHangingState>> binding_states, int i, int j){
    Figure figure;
    std::vector<std::vector<bool>> visited(binding_states.size(), std::vector(binding_states[0].size(), false));
    figure.BuildHangingFigure(visited, game_field_matrix_, binding_states, i, j);
    return figure;
}

std::vector<Figure> Model::MakeHangingFigures(std::vector<std::vector<CellHangingState>>& binding_states){
    std::vector<Figure> figures_to_drop;
    for(int i = 1; i < game_field_matrix_.size()-1; i++){
        for(int j = 1; j < game_field_matrix_[0].size()-1; j++){
            if(binding_states[i][j] == CellHangingState::kHanging && Cell::IsPill(game_field_matrix_[i][j])){
                figures_to_drop.push_back(CreateFigureToDrop(binding_states, i, j));
            }
        }
    }
    return figures_to_drop;
}

void Model::DropFigures(std::vector<Figure>& figures){
    std::vector<Figure> moved_figures;
    for(int i = 0; i < figures.size(); i++){
        if(figures[i].ProcessSelfMove(game_field_matrix_, MoveDirection::kDown)){
            moved_figures.push_back(figures[i]);
        }
    }
    figures = moved_figures;
}

void Model::ChangePill(){
    pill_ = next_pill_;
    next_pill_ = Pill();
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
    emit NextPillChanged(next_pill_.ConvertSelf());
}

void Model::InitializeGameField(){
    int last_row = game_field_matrix_.size();
    for(int i = 0; i < game_field_matrix_[0].size(); i++){
        game_field_matrix_[0][i] = CellState::kOutOfBound;
        game_field_matrix_[last_row-1][i] = CellState::kOutOfBound;
    }
    int last_col = game_field_matrix_[0].size();
    for(int i = 0; i < game_field_matrix_.size(); i++){
        game_field_matrix_[i][0] = CellState::kOutOfBound;
        game_field_matrix_[i][last_col-1] = CellState::kOutOfBound;
    }
}

void Model::PillTurned(){
    pill_.ProcessSelfTurn(game_field_matrix_);
    UpdateGameFieldChanges();
}

void Model::FindSequences(std::vector<ModelCell>& to_delete, GameFieldTable table){
    for(int i = 1; i < table.size()-1; i++){
        int seq = 1;
        CellState sample = table[i][1];
        for(int j = 2; j < table[0].size()-1; j++){
            if(Cell::CheckColorMatch(sample, table[i][j])){
                seq++;
            }
            else{
                if(seq > 3){
                    for(; seq>0; seq--){
                        to_delete.push_back({i,j-seq,table[i][j-seq]});
                    }
                }
                seq = 1;
                sample = table[i][j];
            }
        }
        if(seq > 3){
            for(; seq>0; seq--){
                to_delete.push_back({i, static_cast<int>(table[0].size())-1-seq,
                                     table[i][table[0].size()-1-seq]});
            }
        }
    }
}

void Model::UpdateHangingStates(std::vector<std::vector<CellHangingState>>& hanging_states,
                                std::vector<ModelCell>& to_delete){
    for(int i = 0; i < to_delete.size(); i++){
        if (hanging_states[to_delete[i].x_position+1][to_delete[i].y_position] == CellHangingState::kEnshrined){
            hanging_states[to_delete[i].x_position+1][to_delete[i].y_position] = CellHangingState::kHanging;
        }
        if (hanging_states[to_delete[i].x_position-1][to_delete[i].y_position] == CellHangingState::kEnshrined){
            hanging_states[to_delete[i].x_position-1][to_delete[i].y_position] = CellHangingState::kHanging;
        }
        if (hanging_states[to_delete[i].x_position][to_delete[i].y_position+1] == CellHangingState::kEnshrined){
            hanging_states[to_delete[i].x_position][to_delete[i].y_position+1] = CellHangingState::kHanging;
        }
        if (hanging_states[to_delete[i].x_position][to_delete[i].y_position-1] == CellHangingState::kEnshrined){
            hanging_states[to_delete[i].x_position][to_delete[i].y_position-1] = CellHangingState::kHanging;
        }
        hanging_states[to_delete[i].x_position][to_delete[i].y_position] = CellHangingState::kDeleted;
    }
}

bool Model::RemoveSequences(std::vector<std::vector<CellHangingState>>& hanging_states){
    std::vector<ModelCell> to_delete;
    FindSequences(to_delete, game_field_matrix_);
    UpdateHangingStates(hanging_states, to_delete);
    GameFieldTable transposed(game_field_matrix_[0].size(),
                              std::vector<CellState>(game_field_matrix_.size(), CellState::kEmpty));
    for(int i = 0; i < transposed.size(); i++){
        for(int j = 0; j < transposed[0].size(); j++){
            transposed[i][j] = game_field_matrix_[j][i];
        }
    }
    std::vector<ModelCell> to_delete_transposed;
    FindSequences(to_delete_transposed, transposed);
    for(int i = 0; i < to_delete_transposed.size(); i++){
        std::swap(to_delete_transposed[i].x_position, to_delete_transposed[i].y_position);
    }
    UpdateHangingStates(hanging_states, to_delete_transposed);
    if(to_delete.size() == 0 && to_delete_transposed.size() == 0){
        return false;
    }
    score_ += 100*to_delete_transposed.size();
    score_ += 100*to_delete.size();
    for(int i = 0; i < to_delete.size(); i++){
        if(Cell::IsVirus(game_field_matrix_[to_delete[i].x_position][to_delete[i].y_position])) viruses_count_--;
        game_field_matrix_[to_delete[i].x_position][to_delete[i].y_position] = CellState::kEmpty;
    }
    for(int i = 0; i < to_delete_transposed.size(); i++){
        if(Cell::IsVirus(game_field_matrix_[to_delete_transposed[i].x_position][to_delete_transposed[i].y_position])) viruses_count_--;
        game_field_matrix_[to_delete_transposed[i].x_position][to_delete_transposed[i].y_position] = CellState::kEmpty;
    }
    return true;
}

void Model::ClearField(){
    for(int i = 1; i < game_field_matrix_.size()-1; i++){
        for(int j = 1; j < game_field_matrix_[0].size()-1; j++){
            game_field_matrix_[i][j] = CellState::kEmpty;
        }
    }
}

bool Model::CheckPillAddPossibility(){
    return game_field_matrix_[1][5] == CellState::kEmpty &&
           game_field_matrix_[1][6] == CellState::kEmpty;
}

void Model::ChangeLevel(){
    ClearField();
    level_++;
    GenerateViruses(level_);
    ChangePill();
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
}
