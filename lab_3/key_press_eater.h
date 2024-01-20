#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

//https://doc.qt.io/qt-6/eventsandfilters.html
class KeyPressEater: public QObject{
  Q_OBJECT
  public:
    KeyPressEater(QObject* obj = nullptr);
  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // KEYPRESSEATER_H
