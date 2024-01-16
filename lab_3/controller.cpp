#include <stdexcept>
#include "controller.h"

Controller::Controller(){
    //QObject::connect(this, &Controller::PaintNextFigure, &view, &View::NewNextFigure);
    QObject::connect(this, &Controller::PrintScore, &view, &View::NewScore);
    //QObject::connect(&view, &View::NewInput, this, &Controller::HandleInput);
    //QObject::connect(this, &Controller::MoveCurrentFigure, &model, &Model::FigureMoved);
    //QObject::connect(&model, &Model::ScoreChanged, this, &Controller::ChangeScore);
    //QObject::connect(&model, &Model::NextFigureChanged, this, &Controller::ChangeNextFigure);
    QObject::connect(&model, &Model::GameFieldChanged, &view, &View::NewGameField);
    QObject::connect(this, &Controller::Start, &model, &Model::StartSignalGot);
    emit Start();
}
