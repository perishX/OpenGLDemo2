#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include <QPalette>

class GameObject : public QLabel
{
    Q_OBJECT
public:
    explicit GameObject(QWidget* parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
};

#endif // GAMEOBJECT_H
