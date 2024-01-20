#include <iostream>
#include "view.h"

WidgetWithFigureToPaint::WidgetWithFigureToPaint(QWidget* parent, int rows_count, int columns_count):
    QWidget(parent), rows_count_(rows_count), columns_count_(columns_count){}

void WidgetWithFigureToPaint::SetCells(std::vector<Cell> cells){
    figure_ = cells;
}

void WidgetWithFigureToPaint::Paint(int rows_count, int columns_count){
    int wid = this->width()-100;
    int he = this->height()-100;
    int xsize = wid/columns_count;
    int ysize = he/rows_count;
    QPainter painter;
    painter.begin(this);
    for(int i = 0; i < figure_.size(); i++){
        QBrush brush;
        brush.setColor(figure_[i].color);
        brush.setStyle(figure_[i].style);
        painter.setBrush(brush);
        painter.drawRect(50+figure_[i].x_position * xsize,
                         50+figure_[i].y_position * ysize,
                         xsize, ysize);
    }
    painter.end();
}

GameView::GameView(QWidget *parent): QWidget(parent), game_(new GameField()),
                             next_figure_(new NextFigureField()),
                             score_panel_(new ScorePanel()){
    QVBoxLayout* game_field_layout = new QVBoxLayout();
    game_->setMinimumSize(500, 800);
    game_field_layout->addWidget(game_);

    QVBoxLayout* score_and_next_figure_layout = new QVBoxLayout();
    score_and_next_figure_layout->addStretch(0);
    next_figure_->setMinimumSize(200, 150);
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
    QFont font = QFont();
    font.setPointSize(40);
    scores_->setFont(font);
    scores_->setText("0000000");
    scores_->setAlignment(Qt::AlignCenter);
}

void ScorePanel::ChangeScores(int score){
    scores_->setText(QString::number(score));
    scores_->setAlignment(Qt::AlignCenter);
}

void GameView::NewScore(int score){
    score_panel_->ChangeScores(score);
}

NextFigureField::NextFigureField(QWidget* parent): WidgetWithFigureToPaint(parent, 1, 2) {}

GameField::GameField(QWidget* parent): WidgetWithFigureToPaint(parent){}

void GameField::SetRowsCount(int rows_count){
    rows_count_ = rows_count;
}

void GameField::SetColumnsCount(int vert){
    columns_count_ = vert;
}

void NextFigureField::paintEvent(QPaintEvent* event){
    WidgetWithFigureToPaint::Paint(rows_count_, columns_count_);
}

void GameField::paintEvent(QPaintEvent* event){
    WidgetWithFigureToPaint::Paint(rows_count_, columns_count_);
}

void GameView::NewGameField(std::vector<Cell> game_field, int rows_count, int columns_count){
    game_->SetCells(game_field);
    game_->SetRowsCount(rows_count);
    game_->SetColumnsCount(columns_count);
    QWidget::update();
}

void GameView::NewNextFigure(std::vector<Cell> pill){
    next_figure_->SetCells(pill);
    QWidget::update();
}

void GameView::keyPressEvent(QKeyEvent* e){
    emit NewKeyPressed(e->key());
}

void GameView::ActivationGameFieldChanged(ModelActivationState activation){
    switch (activation){
      case ModelActivationState::kActivate:
        this->setFocusPolicy(Qt::StrongFocus);
      case ModelActivationState::kDeactivate:
        this->setFocusPolicy(Qt::NoFocus);
    }
}
