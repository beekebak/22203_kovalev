#include <iostream>
#include "view.h"

View::View(QWidget *parent): QWidget(parent), game_(new GameField()),
                             next_figure_(new NextFigureField()),
                             score_panel_(new ScorePanel()){
    QVBoxLayout* game_field_layout = new QVBoxLayout();
    game_->setMinimumSize(500, 1000);
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

void GameField::SetCells(std::vector<Cell> cells){
    game_field_ = cells;
}

void GameField::SetRowsCount(int rows_count){
    rows_count_ = rows_count;
}

void GameField::SetColumnsCount(int vert){
    columns_count_ = vert;
}

void GameField::paintEvent(QPaintEvent* event){
    int wid = this->width()-100;
    int he = this->height()-100;
    int xsize = wid/columns_count_;
    int ysize = he/rows_count_;
    QPainter painter;
    painter.begin(this);
    for(int i = 0; i < game_field_.size(); i++){
        QBrush brush;
        brush.setColor(game_field_[i].color);
        brush.setStyle(game_field_[i].style);
        painter.setBrush(brush);
        painter.drawRect(50+game_field_[i].x_position * xsize,
                         50+game_field_[i].y_position * ysize,
                         xsize, ysize);
    }
    painter.end();
}

void View::NewGameField(std::vector<Cell> game_field, int rows_count, int columns_count){
    game_->SetCells(game_field);
    game_->SetRowsCount(rows_count);
    game_->SetColumnsCount(columns_count);
    QWidget::update();
}

void View::keyPressEvent(QKeyEvent* e){
    emit NewKeyPressed(e->key());
}
