#ifndef CELL_H
#define CELL_H

#include <QColor>

enum class CellState{
    kEmpty,
    kOutOfBound,
    kRedPill,
    kBluePill,
    kYellowPill,
    kRedVirus,
    kBlueVirus,
    kYellowVirus
};

struct Cell{
    int x_position;
    int y_position;
    QColor color;
    Qt::BrushStyle style;
    static bool IsPill(CellState state);
    static bool IsVirus(CellState state);
    Cell(int x, int y, QColor input_color, Qt::BrushStyle style);
    static bool CheckColorMatch(CellState sample, CellState cell_to_check);
};

struct ModelCell{
    int x_position = 0;
    int y_position = 0;
    CellState state = CellState::kOutOfBound;
};

enum class CellHangingState{
    kHanging,
    kDeleted,
    kEnshrined
};

#endif // CELL_H
