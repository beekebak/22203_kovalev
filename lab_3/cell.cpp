#include "cell.h"

Cell::Cell(int x, int y, QColor input_color, Qt::BrushStyle input_style):
    x_position(x), y_position(y), color(input_color), style(input_style){}

bool Cell::IsPill(CellState state){
    return state == CellState::kBluePill || state == CellState::kRedPill || state == CellState::kYellowPill;
}

bool Cell::CheckColorMatch(CellState sample, CellState cell_to_check){
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
