#include <random>
#include <map>
#include "model.h"

void Figure::AddSelfToGameField(GameFieldTable& game_field_matrix_){
    for(int i = 0; i < figure_.size(); i++){
        game_field_matrix_[figure_[i].x_position][figure_[i].y_position] =
            figure_[i].state;
    }
}

void Figure::RemoveSelfFromGameField(GameFieldTable& game_field_matrix_){
    for(int i = 0; i < figure_.size(); i++){
        game_field_matrix_[figure_[i].x_position][figure_[i].y_position] = CellState::kEmpty;
    }
}

Pill::Pill(){
    static std::map<int, CellState> pills = {{0, CellState::kYellowPill},
                                             {1, CellState::kBluePill},
                                             {2, CellState::kRedPill}};
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    figure_.push_back(ModelCell{1,5,pills[rng()%3]});
    figure_.push_back(ModelCell{1,6,pills[rng()%3]});
}

Figure Figure::FindBorder(MoveDirection direction){
    if(direction == MoveDirection::kDown){
        return FindBottom();
    }
    else if(direction == MoveDirection::kLeft){
        return FindLeftBorder();
    }
    else if(direction == MoveDirection::kRight){
        return FindRightBorder();
    }
}

void Figure::DetermineShift(int& x_shift, int& y_shift, MoveDirection direction){
    if(direction == MoveDirection::kDown){
        x_shift = 1;
        y_shift = 0;
    }
    if(direction == MoveDirection::kRight){
        x_shift = 0;
        y_shift = 1;
    }
    if(direction == MoveDirection::kLeft){
        x_shift = 0;
        y_shift = -1;
    }
}

Figure Figure::FindBottom(){
    std::unordered_map<int, ModelCell> lowest_cells_of_figure;
    for(int i = 0; i < figure_.size(); i++){
        if(lowest_cells_of_figure.find(figure_[i].y_position) == lowest_cells_of_figure.end() ||
            lowest_cells_of_figure[figure_[i].y_position].x_position < figure_[i].x_position){
            lowest_cells_of_figure[figure_[i].y_position] = figure_[i];
        }
    }
    Figure bottom;
    for(auto const &cell:lowest_cells_of_figure){
        bottom.figure_.push_back(cell.second);
    }
    return bottom;
}

Figure Figure::FindLeftBorder(){
    std::unordered_map<int, ModelCell> lowest_cells_of_figure;
    for(int i = 0; i < figure_.size(); i++){
        if(lowest_cells_of_figure.find(figure_[i].x_position) == lowest_cells_of_figure.end() ||
            lowest_cells_of_figure[figure_[i].x_position].y_position > figure_[i].y_position){
            lowest_cells_of_figure[figure_[i].x_position] = figure_[i];
        }
    }
    Figure left_border;
    for(auto const &cell:lowest_cells_of_figure){
        left_border.figure_.push_back(cell.second);
    }
    return left_border;
}

Figure Figure::FindRightBorder(){
    std::unordered_map<int, ModelCell> lowest_cells_of_figure;
    for(int i = 0; i < figure_.size(); i++){
        if(lowest_cells_of_figure.find(figure_[i].x_position) == lowest_cells_of_figure.end() ||
            lowest_cells_of_figure[figure_[i].x_position].y_position < figure_[i].y_position){
            lowest_cells_of_figure[figure_[i].x_position] = figure_[i];
        }
    }
    Figure bottom;
    for(auto const &cell:lowest_cells_of_figure){
        bottom.figure_.push_back(cell.second);
    }
    return bottom;
}

bool Figure::CheckIfCanMove(GameFieldTable& game_field_matrix, int x_shift, int y_shift){
    for(int i = 0; i < figure_.size(); i++){
        if(game_field_matrix[figure_[i].x_position+x_shift][figure_[i].y_position+y_shift] != CellState::kEmpty){
            return false;
        }
    }
    return true;
}

void Figure::MoveFigure(int x_shift, int y_shift){
    for(int i = 0; i < figure_.size(); i++){
        figure_[i].x_position += x_shift;
        figure_[i].y_position += y_shift;
    }
}

bool Figure::ProcessSelfMove(GameFieldTable& game_field_matrix, MoveDirection direction){
    int x_shift = 0;
    int y_shift = 0;
    DetermineShift(x_shift, y_shift, direction);
    Figure border = FindBorder(direction);
    bool drop_is_avialable = border.CheckIfCanMove(game_field_matrix, x_shift, y_shift);
    if(drop_is_avialable){
        RemoveSelfFromGameField(game_field_matrix);
        MoveFigure(x_shift, y_shift);
        AddSelfToGameField(game_field_matrix);
        return true;
    }
    return false;
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
    PillOrientation orientation = DetermineOrientation();
    bool turn_is_avialable = CheckIfCanTurn(game_field_matrix, orientation);
    if(turn_is_avialable){
        RemoveSelfFromGameField(game_field_matrix);
        TurnSelf(orientation);
        AddSelfToGameField(game_field_matrix);
    }
}
