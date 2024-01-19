#include <stdexcept>
#include <Qt>
#include "controller.h"

Controller::Controller(){
    //QObject::connect(this, &Controller::PaintNextFigure, &view, &GameView::NewNextFigure);
    QObject::connect(this, &Controller::PrintScore, &game_view, &GameView::NewScore);
    QObject::connect(&game_view, &GameView::NewKeyPressed, this, &Controller::HandleInputedKey);
    QObject::connect(this, &Controller::MoveCurrentPill, &model, &Model::PillMoved);
    QObject::connect(this, &Controller::TurnPill, &model, &Model::PillTurned);
    //QObject::connect(&model, &Model::ScoreChanged, this, &Controller::ChangeScore);
    //QObject::connect(&model, &Model::NextFigureChanged, this, &Controller::ChangeNextFigure);
    QObject::connect(&model, &Model::GameFieldChanged, &game_view, &GameView::NewGameField);
    QObject::connect(&model, &Model::ChangeActivationOfGameField, &game_view, &GameView::ActivationGameFieldChanged);
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
