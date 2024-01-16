#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"
#include "model.h"


class Controller: public QObject
{
    Q_OBJECT
  public:
    View view;
    Controller();
  signals:
    void PrintScore(int score);
    void Start();
    //void PaintNextFigure();
    //void MoveCurrentFigure();
  public slots:
    //void ChangeScore();
    //void ChangeNextFigure();
    //void HandleInput();
  private:
    Model model;
};

#endif // CONTROLLER_H
