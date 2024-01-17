#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include <QObject>
#include <QColor>
#include <QTimer>

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

using GameFieldTable = std::vector<std::vector<CellState>>;

struct Cell{
    int x_position;
    int y_position;
    QColor color;
    Qt::BrushStyle style;
    Cell(int x, int y, QColor input_color, Qt::BrushStyle style);
};

struct ModelCell{
    int x_position = 0;
    int y_position = 0;
    CellState state = CellState::kOutOfBound;
};

class Figure{
  protected:
    Figure FindBottomOfFigure();
    bool CheckIfCanDrop(GameFieldTable& game_field_matrix_);
    void DropFigureByOneTile();
    std::vector<ModelCell> figure_;
  public:
    void AddSelfToGameField(GameFieldTable& game_field_matrix_);
    void RemoveSelfFromGameField(GameFieldTable& game_field_matrix_);
    bool ProcessSelfFall(GameFieldTable& game_field_matrix_);
};

class Pill: public Figure{
  public:
    Pill();
};

class Model: public QObject
{
  Q_OBJECT
  public:
    GameFieldTable game_field_matrix_;
    Model();
  private:
    Pill pill_;
    void UpdateGameFieldChanges();
    void GenerateViruses();
    Figure GenerateNewPill();
  signals:
    void GameFieldChanged(std::vector<Cell> cells, int x_size, int y_size);
  //  void ScoreChanged();
  //  void NextFigureChanged();
  public slots:
    void StartSignalGot();
    void PillDrop();
  //  void FigureMoved();
};

#endif // MODEL_H
