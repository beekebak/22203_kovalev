#ifndef PILL_H
#define PILL_H

#include "figure.h"

enum class PillOrientation{
    kHorizontal,
    kVertical
};

class Pill: public Figure{
public:
    Pill();
    void ProcessSelfTurn(GameFieldTable& game_field_matrix_);
    bool is_locked = false;
private:
    PillOrientation DetermineOrientation();
    bool CheckIfCanTurn(GameFieldTable game_field_matrix, PillOrientation orientation);
    void TurnSelf(PillOrientation orientation);
};

#endif // PILL_H
