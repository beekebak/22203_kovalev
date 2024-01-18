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

enum class MoveDirection{
    kRight,
    kLeft,
    kDown
};

enum class PillOrientation{
    kHorizontal,
    kVertical
};

enum class CellHangingState{
    kHanging,
    kDeleted,
    kEnshrined
};

using GameFieldTable = std::vector<std::vector<CellState>>;

struct Cell{
    int x_position;
    int y_position;
    QColor color;
    Qt::BrushStyle style;
    bool static IsPill(CellState state);
    Cell(int x, int y, QColor input_color, Qt::BrushStyle style);
};

struct ModelCell{
    int x_position = 0;
    int y_position = 0;
    CellState state = CellState::kOutOfBound;
};

class Figure{
  protected:
    Figure FindBorder(MoveDirection direction);
    Figure FindBottom();
    Figure FindLeftBorder();
    Figure FindRightBorder();
    void DetermineShift(int& x_shift, int& y_shift, MoveDirection direction);
    bool CheckIfCanMove(GameFieldTable& game_field_matrix_, int x_shift, int y_shift);
    void MoveFigure(int x_shift, int y_shift);
    std::vector<ModelCell> figure_;
  public:
    void BuildHangingFigure(std::vector<std::vector<bool>>& visited, GameFieldTable& game_field,
                            std::vector<std::vector<CellHangingState>>& binding_states, int i, int j);
    void AddSelfToGameField(GameFieldTable& game_field_matrix_);
    void RemoveSelfFromGameField(GameFieldTable& game_field_matrix_);
    bool ProcessSelfMove(GameFieldTable& game_field_matrix_, MoveDirection direction);
};

class Pill: public Figure{
  public:
    Pill();
    void ProcessSelfTurn(GameFieldTable& game_field_matrix_);
    bool is_locked = false;
  private:
    PillOrientation DetermineOrientation();
    bool CheckIfCanTurn(GameFieldTable game_field_matrix, PillOrientation orientation);
    void TurnSelf(PillOrientation orientation);
};

class Model: public QObject
{
  Q_OBJECT
  public:
    Model();
  private:
    GameFieldTable game_field_matrix_;
    Pill pill_;
    void Delay();
    std::vector<Figure> MakeHangingFigures(std::vector<std::vector<CellHangingState>>& binding_states);
    void DropFigures(std::vector<Figure>& figures);
    bool CheckColorMatch(CellState sample, CellState cell_to_check);
    void FindSequences(std::vector<ModelCell>& to_delete, GameFieldTable table);
    void UpdateHangingStates(std::vector<std::vector<CellHangingState>>& hanging_states,
                             std::vector<ModelCell>& to_delete);
    bool RemoveSequences(std::vector<std::vector<CellHangingState>>& hanging_states);
    void ChangePill();
    void InitializeGameField();
    void UpdateGameFieldChanges();
    void GenerateViruses();
    Figure GenerateNewPill();
    Figure CreateFigureToDrop(std::vector<std::vector<CellHangingState>> binding_states, int i, int j);
  signals:
    void GameFieldChanged(std::vector<Cell> cells, int x_size, int y_size);
  //  void ScoreChanged();
  //  void NextFigureChanged();
  public slots:
    void StartSignalGot();
    bool PillMoved(MoveDirection direction);
    void PillTurned();
    void PillMoveDownByTime();
};

#endif // MODEL_H
