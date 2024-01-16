#include <random>
#include <map>
#include "model.h"

TetrisCell::TetrisCell(int x, int y, QColor input_color, Qt::BrushStyle input_style):
    x_position(x), y_position(y), color(input_color), style(input_style){}


Model::Model(){
    game_field_matrix_ = std::vector<std::vector<CellState>>(20,
                                std::vector<CellState>(10, CellState::kEmpty));
    GenerateViruses();
}

void Model::GenerateViruses(){
    static std::map<int, CellState> viruses = {{0, CellState::kYellowVirus},
                                               {1, CellState::kBlueVirus},
                                               {2, CellState::kRedVirus}};
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    int count = rng()%8+2;
    for(int i = 0; i < count; i++){
        int virus_place = rng()%200;
        game_field_matrix_[virus_place/10][virus_place%20] = viruses[rng()%3];
    }
}

void Model::UpdateGameFieldChanges(){
    std::vector<TetrisCell> cells;
    for(int i = 0; i < game_field_matrix_.size(); i++){
        for(int j = 0; j < game_field_matrix_[0].size(); j++){
            switch(game_field_matrix_[i][j]){
            case CellState::kRedPill:
                cells.push_back({i, j, Qt::red, Qt::SolidPattern});
                break;
            case CellState::kBluePill:
                cells.push_back({i, j, Qt::blue, Qt::SolidPattern});
                break;
            case CellState::kYellowPill:
                cells.push_back({i, j, Qt::yellow, Qt::SolidPattern});
                break;
            case CellState::kRedVirus:
                cells.push_back({i, j, Qt::red, Qt::CrossPattern});
                break;
            case CellState::kBlueVirus:
                cells.push_back({i, j, Qt::blue, Qt::CrossPattern});
                break;
            case CellState::kYellowVirus:
                cells.push_back({i, j, Qt::yellow, Qt::CrossPattern});
                break;
            case CellState::kOutOfBound:
                throw std::runtime_error("wrong game field matrix format");
                break;
            case CellState::kEmpty:
                break;
            }
        }
    }
    emit GameFieldChanged(cells, game_field_matrix_.size(), game_field_matrix_[0].size());
}

void Model::StartSignalGot(){
    UpdateGameFieldChanges();
}
