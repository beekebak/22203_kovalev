#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QString>

#include "model.h"

class GameField: public QWidget{
  public:
    GameField(QWidget* parent = nullptr);
    void SetCells(std::vector<TetrisCell>);
    void SetHorizontalCellsCount(int hor);
    void SetVerticalCellsCount(int vert);
  private:
    int horizontal_sells_count;
    int vertical_sells_count;
    std::vector<TetrisCell> active_cells_;
    void paintEvent(QPaintEvent*) override;
};

class NextFigureField: public QWidget{
  public:
    NextFigureField(QWidget* parent = nullptr);
    void SetFigure(std::vector<TetrisCell> figure);
  private:
    std::vector<TetrisCell> figure_;
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
  signals:
    //void NewInput();
  public slots:
    void NewGameField(std::vector<TetrisCell> cells, int x, int y);
    void NewScore(int score);
    //void NewNextFigure();
};

#endif // VIEW_H
