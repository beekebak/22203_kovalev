#include <random>
#include <map>
#include <exception>
#include "pill.h"

Pill::Pill(){
    static std::map<int, CellState> pills = {{0, CellState::kYellowPill},
                                             {1, CellState::kBluePill},
                                             {2, CellState::kRedPill}};
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    figure_.push_back(ModelCell{1,5,pills[rng()%3]});
    figure_.push_back(ModelCell{1,6,pills[rng()%3]});
}

PillOrientation Pill::DetermineOrientation(){
    if(figure_[0].x_position == figure_[1].x_position){
        return PillOrientation::kHorizontal;
    }
    else{
        return PillOrientation::kVertical;
    }
}

bool Pill::CheckIfCanTurn(GameFieldTable game_field_matrix, PillOrientation orientation){
    if(orientation == PillOrientation::kHorizontal){
        return game_field_matrix[figure_[0].x_position-1][figure_[0].y_position+1] == CellState::kEmpty;
    }
    else{
        return game_field_matrix[figure_[0].x_position+1][figure_[0].y_position-1] == CellState::kEmpty;
    }
}

void Pill::TurnSelf(PillOrientation orientation){
    if(orientation == PillOrientation::kHorizontal){
        figure_[0].x_position--;
        figure_[0].y_position++;
    }
    else{
        figure_[0].x_position++;
        figure_[1].y_position--;
        std::swap(figure_[0], figure_[1]);
    }
}

void Pill::ProcessSelfTurn(GameFieldTable& game_field_matrix){
    if(is_locked) return;
    PillOrientation orientation = DetermineOrientation();
    bool turn_is_avialable = CheckIfCanTurn(game_field_matrix, orientation);
    if(turn_is_avialable){
        RemoveSelfFromGameField(game_field_matrix);
        TurnSelf(orientation);
        AddSelfToGameField(game_field_matrix);
    }
}

std::vector<Cell> Pill::ConvertSelf(){
    std::vector<Cell> converted_pill;
    for(int i = 0; i < figure_.size(); i++){
        switch(figure_[i].state){
          case CellState::kRedPill:
            converted_pill.push_back({i, 0, Qt::red, Qt::SolidPattern});
            break;
          case CellState::kBluePill:
            converted_pill.push_back({i, 0, Qt::blue, Qt::SolidPattern});
            break;
          case CellState::kYellowPill:
            converted_pill.push_back({i, 0, Qt::yellow, Qt::SolidPattern});
            break;
          default:
            throw std::runtime_error("pill conversion failed");
        }
    }
    return converted_pill;
}
