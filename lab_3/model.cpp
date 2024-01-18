#include <random>
#include <map>
#include <iostream>
#include <QTime>
#include <QCoreApplication>

#include "model.h"

Cell::Cell(int x, int y, QColor input_color, Qt::BrushStyle input_style):
    x_position(x), y_position(y), color(input_color), style(input_style){}

Model::Model(){
    game_field_matrix_ = GameFieldTable(22,
                                std::vector<CellState>(12, CellState::kEmpty));
    InitializeGameField();
    GenerateViruses();
    pill_ = Pill();
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Model::PillMoveDownByTime);
    timer->start(1000);
}

void Model::GenerateViruses(){
    static std::map<int, CellState> viruses = {{0, CellState::kYellowVirus},
                                               {1, CellState::kBlueVirus},
                                               {2, CellState::kRedVirus}};
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    int count = rng()%8+2;
    for(int i = 0; i < count; i++){
        int virus_place = rng()%160+40;
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
}

void Model::StartSignalGot(){
    UpdateGameFieldChanges();
}

bool Model::PillMoved(MoveDirection direction){
    if(pill_.is_locked) return true;
    bool move_is_done = pill_.ProcessSelfMove(game_field_matrix_, direction);
    UpdateGameFieldChanges();
    return move_is_done;
}

void Model::Delay(){
    QTime die_time = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < die_time)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Model::PillMoveDownByTime(){
    if(!PillMoved(MoveDirection::kDown)){
        std::vector<std::vector<CellHangingState>> binding_states(game_field_matrix_.size(),
                            std::vector<CellHangingState>(game_field_matrix_[0].size(), CellHangingState::kEnshrined));
        while(1){
            if(!RemoveSequences(binding_states)) break;
            pill_.is_locked = true;
            std::vector<Figure> figures_to_drop = MakeHangingFigures(binding_states);
            while(figures_to_drop.size() > 0){
                DropFigures(figures_to_drop);
                UpdateGameFieldChanges();
                Delay();
            }
        }
        ChangePill();
    }
}

bool Cell::IsPill(CellState state){
    return state == CellState::kBluePill || state == CellState::kRedPill || state == CellState::kYellowPill;
}

void Figure::BuildHangingFigure(std::vector<std::vector<bool>>& visited, GameFieldTable& game_field,
                                std::vector<std::vector<CellHangingState>>& binding_states, int i, int j){
    if(Cell::IsPill(game_field[i][j]) && !visited[i][j]){
        figure_.push_back({i, j, game_field[i][j]});
        visited[i][j] = true;
        if(i-1 >= 1) BuildHangingFigure(visited, game_field, binding_states, i-1, j);
        if(j-1 >= 1) BuildHangingFigure(visited, game_field, binding_states, i, j-1);
        if(i-1 < binding_states.size()-1) BuildHangingFigure(visited, game_field, binding_states, i+1, j);
        if(j-1 < binding_states[0].size()-1) BuildHangingFigure(visited, game_field, binding_states, i, j+1);
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
    pill_ = Pill();
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
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

bool Model::CheckColorMatch(CellState sample, CellState cell_to_check){
    switch(sample){
      case CellState::kRedVirus:
      case CellState::kRedPill:
        return cell_to_check == CellState::kRedPill || cell_to_check == CellState::kRedVirus;
      case CellState::kBlueVirus:
      case CellState::kBluePill:
        return cell_to_check == CellState::kBluePill || cell_to_check == CellState::kBlueVirus;
      case CellState::kYellowVirus:
      case CellState::kYellowPill:
        return cell_to_check == CellState::kYellowPill || cell_to_check == CellState::kYellowVirus;
      default:
        return false;
    }
}

void Model::FindSequences(std::vector<ModelCell>& to_delete, GameFieldTable table){
    for(int i = 1; i < table.size()-1; i++){
        int seq = 1;
        CellState sample = table[i][1];
        for(int j = 2; j < table[0].size()-1; j++){
            if(CheckColorMatch(sample, table[i][j])){
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
    for(int i = 0; i < to_delete.size(); i++){
        game_field_matrix_[to_delete[i].x_position][to_delete[i].y_position] = CellState::kEmpty;
    }
    for(int i = 0; i < to_delete_transposed.size(); i++){
        game_field_matrix_[to_delete_transposed[i].x_position][to_delete_transposed[i].y_position] = CellState::kEmpty;
    }
    return true;
}
