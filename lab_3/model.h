#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include <QObject>
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

struct TetrisCell{
    int x_position;
    int y_position;
    QColor color;
    Qt::BrushStyle style;
    TetrisCell(int x, int y, QColor input_color, Qt::BrushStyle style);
};

class Model: public QObject
{
  Q_OBJECT
  public:
    std::vector<std::vector<CellState>> game_field_matrix_;
    Model();
  private:
    void UpdateGameFieldChanges();
    void GenerateViruses();
  signals:
    void GameFieldChanged(std::vector<TetrisCell> cells, int x_size, int y_size);
  //  void ScoreChanged();
  //  void NextFigureChanged();
  public slots:
    void StartSignalGot();
  //  void FigureMoved();
};

#endif // MODEL_H
