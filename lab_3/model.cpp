#include <random>
#include <map>
#include <iostream>
#include "model.h"

Cell::Cell(int x, int y, QColor input_color, Qt::BrushStyle input_style):
    x_position(x), y_position(y), color(input_color), style(input_style){}

Model::Model(){
    game_field_matrix_ = GameFieldTable(20,
                                std::vector<CellState>(10, CellState::kEmpty));
    GenerateViruses();
    pill_ = Pill();
    pill_.AddSelfToGameField(game_field_matrix_);
    UpdateGameFieldChanges();
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Model::PillDrop);
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
        game_field_matrix_[virus_place/10][virus_place%10] = viruses[rng()%3];
    }
}

void Model::UpdateGameFieldChanges(){
    std::vector<Cell> game_field_cells;
    for(int i = 0; i < game_field_matrix_.size(); i++){
        for(int j = 0; j < game_field_matrix_[0].size(); j++){
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

void Model::PillDrop(){
    pill_.ProcessSelfFall(game_field_matrix_);
    UpdateGameFieldChanges();
}
