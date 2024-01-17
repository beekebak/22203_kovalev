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

class Model: public QObject
{
  Q_OBJECT
  public:
    std::vector<std::vector<CellState>> game_field_matrix_;
    Model();
  private:
    struct Figure{
        Figure FindBottomOfFigure();
        bool CheckIfCanDrop(std::vector<std::vector<CellState>> game_field_matrix_);
        void DropFigureByOneTile();
        std::vector<ModelCell> figure_;
    };

    Figure pill_;
    void AddFigureToGameField(Figure& figure);
    void RemoveFigureFromGameField(Figure& figure);
    void UpdateGameFieldChanges();
    void GenerateViruses();
    Figure GenerateNewPill();
    bool ProcessFigureFall(Figure& figure);
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
