#include <random>
#include <map>
#include <iostream>
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

void Model::PillMoved(MoveDirection direction){
    pill_.ProcessSelfMove(game_field_matrix_, direction);
    UpdateGameFieldChanges();
}

void Model::PillMoveDownByTime(){
    PillMoved(MoveDirection::kDown);
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
