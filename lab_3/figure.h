#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "cell.h"

using GameFieldTable = std::vector<std::vector<CellState>>;

enum class MoveDirection{
    kRight,
    kLeft,
    kDown
};

class Figure{
  protected:
    Figure FindBorder(MoveDirection direction);
    Figure FindBottom();
    Figure FindLeftBorder();
    Figure FindRightBorder();
    void DetermineShift(int& x_shift, int& y_shift, MoveDirection direction);
    bool CheckIfCanMove(GameFieldTable& game_field_matrix_, int x_shift, int y_shift);
    void MoveFigure(int x_shift, int y_shift);
    std::vector<ModelCell> figure_;
  public:
    void BuildHangingFigure(std::vector<std::vector<bool>>& visited, GameFieldTable& game_field,
                            std::vector<std::vector<CellHangingState>>& binding_states, int i, int j);
    void AddSelfToGameField(GameFieldTable& game_field_matrix_);
    void RemoveSelfFromGameField(GameFieldTable& game_field_matrix_);
    bool ProcessSelfMove(GameFieldTable& game_field_matrix_, MoveDirection direction);
};

#endif // FIGURE_H
