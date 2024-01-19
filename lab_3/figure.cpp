#include <random>
#include <map>
#include "figure.h"

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
