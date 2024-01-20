#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include <QObject>
#include <QColor>
#include <QTimer>

#include "figure.h"
#include "pill.h"
#include "key_press_eater.h"

enum class ModelActivationState{
    kActivate,
    kDeactivate
};

class Model: public QObject
{
  Q_OBJECT
  public:
    Model();
  private:
    bool CheckPillAddPossibility();
    void ClearField();
    void ChangeLevel();
    void Delay();
    void InitializeGameField();
    void GenerateViruses(int level);
    void ChangePill();
    void UpdateGameFieldChanges();
    void DropFigures(std::vector<Figure>& figures);
    void FindSequences(std::vector<ModelCell>& to_delete, GameFieldTable table);
    void UpdateHangingStates(std::vector<std::vector<CellHangingState>>& hanging_states,
                             std::vector<ModelCell>& to_delete);
    bool RemoveSequences(std::vector<std::vector<CellHangingState>>& hanging_states);
    Figure CreateFigureToDrop(std::vector<std::vector<CellHangingState>> binding_states, int i, int j);
    GameFieldTable game_field_matrix_;
    Pill pill_;
    Pill next_pill_;
    int viruses_count_;
    int score_;
    int level_;
    std::vector<Figure> MakeHangingFigures(std::vector<std::vector<CellHangingState>>& binding_states);
  signals:
    void GameFieldChanged(std::vector<Cell> cells, int x_size, int y_size);
    void ChangeActivationOfGameField(ModelActivationState activation);
    void ScoreChanged(int score);
    void NextPillChanged(std::vector<Cell> pill);
  public slots:
    void StartSignalGot();
    bool PillMoved(MoveDirection direction);
    void PillTurned();
    void PillMoveDownByTime();
};

#endif // MODEL_H
