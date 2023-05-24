#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <iostream>

class MyPushButton:public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // MYPUSHBUTTON_H
