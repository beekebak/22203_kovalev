#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QString>
#include <QKeyEvent>

#include "model.h"

class GameField: public QWidget{
  public:
    GameField(QWidget* parent = nullptr);
    void SetCells(std::vector<Cell>);
    void SetRowsCount(int row_size);
    void SetColumnsCount(int column_size);
  private:
    int rows_count_;
    int columns_count_;
    std::vector<Cell> game_field_;
    void paintEvent(QPaintEvent*) override;
};

class NextFigureField: public QWidget{
  public:
    NextFigureField(QWidget* parent = nullptr);
    void SetFigure(std::vector<Cell> figure);
  private:
    std::vector<Cell> figure_;
    //void paintEvent(QPaintEvent*) override;
};

class ScorePanel: public QWidget{
  public:
    ScorePanel(QWidget* parent = nullptr);
    void ChangeScores(int scores);
  private:
    QLabel* scores_;
};

class View: public QWidget{
    Q_OBJECT
  public:
    View(QWidget* parent = nullptr);
  private:
    GameField* game_;
    NextFigureField* next_figure_;
    ScorePanel* score_panel_;
    void keyPressEvent(QKeyEvent* e) override;
  signals:
    void NewKeyPressed(int key_code);
  public slots:
    void NewGameField(std::vector<Cell> cells, int x, int y);
    void NewScore(int score);
    //void NewNextFigure();
};

#endif // VIEW_H
