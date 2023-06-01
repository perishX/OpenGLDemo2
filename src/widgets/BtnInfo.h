#ifndef BTNINFO_H
#define BTNINFO_H

#include <QPushButton>
#include <QMouseEvent>
#include <iostream>

class BtnInfo:public QPushButton
{
    Q_OBJECT
public:
    explicit BtnInfo(QWidget *parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *event);
private:

};

#endif // BTNINFO_H
