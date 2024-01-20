#include <stdexcept>
#include <Qt>
#include "controller.h"

Controller::Controller(){
    QObject::connect(&model, &Model::ScoreChanged, &view, &GameView::NewScore);
    QObject::connect(&view, &GameView::NewKeyPressed, this, &Controller::HandleInputedKey);
    QObject::connect(this, &Controller::MoveCurrentPill, &model, &Model::PillMoved);
    QObject::connect(this, &Controller::TurnPill, &model, &Model::PillTurned);
    QObject::connect(&model, &Model::NextPillChanged, &view, &GameView::NewNextFigure);
    QObject::connect(&model, &Model::GameFieldChanged, &view, &GameView::NewGameField);
    QObject::connect(&model, &Model::ChangeActivationOfGameField, &view, &GameView::ActivationGameFieldChanged);
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
