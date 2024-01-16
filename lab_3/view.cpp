#include <iostream>
#include "view.h"

View::View(QWidget *parent): QWidget(parent), game_(new GameField()),
                             next_figure_(new NextFigureField()),
                             score_panel_(new ScorePanel()){
    QVBoxLayout* game_field_layout = new QVBoxLayout();
    game_->setMinimumSize(500, 500);
    game_field_layout->addWidget(game_);

    QVBoxLayout* score_and_next_figure_layout = new QVBoxLayout();
    score_and_next_figure_layout->addStretch(0);
    next_figure_->setMinimumSize(200, 200);
    score_and_next_figure_layout->addWidget(next_figure_);
    score_and_next_figure_layout->addStretch(0);
    score_panel_->setMinimumSize(200, 200);
    score_and_next_figure_layout->addWidget(score_panel_);
    score_and_next_figure_layout->addStretch(0);

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->addStretch(0);
    main_layout->addLayout(game_field_layout);
    main_layout->addLayout(score_and_next_figure_layout);
    main_layout->addStretch(0);

    this->show();
}

ScorePanel::ScorePanel(QWidget* parent): QWidget(parent), scores_(new QLabel(this)){
    scores_->setText("00000");
    scores_->setAlignment(Qt::AlignCenter);
}

void ScorePanel::ChangeScores(int score){
    scores_->setText(QString::number(score));
}

void View::NewScore(int score){
    score_panel_->ChangeScores(score);
}

NextFigureField::NextFigureField(QWidget* parent): QWidget(parent){}

GameField::GameField(QWidget* parent): QWidget(parent) {}

void GameField::SetCells(std::vector<TetrisCell> cells){
    active_cells_ = cells;
}

void GameField::SetHorizontalCellsCount(int hor){
    horizontal_sells_count = hor;
}

void GameField::SetVerticalCellsCount(int vert){
    vertical_sells_count = vert;
}

//void NextFigureField::paintEvent(QPaintEvent* event){
//    ActualPaint(10,20);
//}

void GameField::paintEvent(QPaintEvent* event){
    int wid = this->width()-100;
    int he = this->height()-100;
    int xsize = wid/horizontal_sells_count;
    int ysize = he/vertical_sells_count;
    QPainter painter;
    painter.begin(this);
    for(int i = 0; i < active_cells_.size(); i++){
        QBrush brush;
        brush.setColor(active_cells_[i].color);
        brush.setStyle(active_cells_[i].style);
        painter.setBrush(brush);
        painter.drawRect(50+active_cells_[i].x_position * xsize,
                         50+active_cells_[i].y_position * ysize,
                         xsize, ysize);
    }
    painter.end();
}

void View::NewGameField(std::vector<TetrisCell> cells, int x, int y){
    game_->SetCells(cells);
    game_->SetHorizontalCellsCount(x);
    game_->SetVerticalCellsCount(y);
    paintEvent(NULL);
}

