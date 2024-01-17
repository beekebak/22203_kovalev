#include <stdexcept>
#include <Qt>
#include "controller.h"

Controller::Controller(){
    //QObject::connect(this, &Controller::PaintNextFigure, &view, &View::NewNextFigure);
    QObject::connect(this, &Controller::PrintScore, &view, &View::NewScore);
    QObject::connect(&view, &View::NewKeyPressed, this, &Controller::HandleInputedKey);
    QObject::connect(this, &Controller::MoveCurrentPill, &model, &Model::PillMoved);
    QObject::connect(this, &Controller::TurnPill, &model, &Model::PillTurned);
    //QObject::connect(&model, &Model::ScoreChanged, this, &Controller::ChangeScore);
    //QObject::connect(&model, &Model::NextFigureChanged, this, &Controller::ChangeNextFigure);
    QObject::connect(&model, &Model::GameFieldChanged, &view, &View::NewGameField);
    QObject::connect(this, &Controller::Start, &model, &Model::StartSignalGot);
    emit Start();
}

void Controller::HandleInputedKey(int key_code){
    if(key_code == Qt::Key_Left){
        emit MoveCurrentPill(MoveDirection::kLeft);
    }
    if(key_code == Qt::Key_Down){
        emit MoveCurrentPill(MoveDirection::kDown);
    }
    if(key_code == Qt::Key_Right){
        emit MoveCurrentPill(MoveDirection::kRight);
    }
    if(key_code == Qt::Key_Up){
        emit TurnPill();
    }
}
