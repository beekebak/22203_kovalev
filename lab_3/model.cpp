#include <random>
#include <map>
#include <iostream>
#include "model.h"

Cell::Cell(int x, int y, QColor input_color, Qt::BrushStyle input_style):
    x_position(x), y_position(y), color(input_color), style(input_style){}

void Model::AddFigureToGameField(Figure& figure){
    for(int i = 0; i < figure.figure_.size(); i++){
        game_field_matrix_[figure.figure_[i].x_position][figure.figure_[i].y_position] =
            figure.figure_[i].state;
    }
}

void Model::RemoveFigureFromGameField(Figure& figure){
    for(int i = 0; i < figure.figure_.size(); i++){
        game_field_matrix_[figure.figure_[i].x_position][figure.figure_[i].y_position] = CellState::kEmpty;
    }
}

Model::Model(){
    game_field_matrix_ = std::vector<std::vector<CellState>>(20,
                                std::vector<CellState>(10, CellState::kEmpty));
    GenerateViruses();
    pill_ = GenerateNewPill();
    AddFigureToGameField(pill_);
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

Model::Figure Model::GenerateNewPill(){
    static std::map<int, CellState> pills = {{0, CellState::kYellowPill},
                                               {1, CellState::kBluePill},
                                               {2, CellState::kRedPill}};
    Figure pill;
    auto rd = std::random_device();
    std::mt19937 rng = std::mt19937(rd());
    pill.figure_.push_back(ModelCell{0,4,pills[rng()%3]});
    pill.figure_.push_back(ModelCell{0,5,pills[rng()%3]});
    return pill;
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


Model::Figure Model::Figure::FindBottomOfFigure(){
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

bool Model::Figure::CheckIfCanDrop(std::vector<std::vector<CellState>> game_field_matrix){
    for(int i = 0; i < figure_.size(); i++){
        if(game_field_matrix[figure_[i].x_position+1][figure_[i].y_position] != CellState::kEmpty){
            return false;
        }
    }
    return true;
}

void Model::Figure::DropFigureByOneTile(){
    for(int i = 0; i < figure_.size(); i++){
        figure_[i].x_position++;
    }
}

bool Model::ProcessFigureFall(Figure& figure){
    Figure bottom = figure.FindBottomOfFigure();
    bool drop_is_avialable = bottom.CheckIfCanDrop(game_field_matrix_);
    if(drop_is_avialable){
        RemoveFigureFromGameField(figure);
        figure.DropFigureByOneTile();
        AddFigureToGameField(figure);
        return true;
    }
    return false;
}

void Model::PillDrop(){
    ProcessFigureFall(pill_);
    UpdateGameFieldChanges();
}
