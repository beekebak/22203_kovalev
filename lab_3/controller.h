#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"
#include "model.h"


class Controller: public QObject
{
    Q_OBJECT
  public:
    GameView game_view;
    Controller();
  signals:
    void PrintScore(int score);
    void Start();
    //void PaintNextPill();
    void MoveCurrentPill(MoveDirection direction);
    void TurnPill();
  public slots:
    //void ChangeScore();
    //void ChangeNextFigure();
    void HandleInputedKey(int key_code);
  private:
    Model model;
};

#endif // CONTROLLER_H
