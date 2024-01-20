#include "key_press_eater.h"

KeyPressEater::KeyPressEater(QObject* obj): QObject(obj){}

bool KeyPressEater::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        return true;
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}
