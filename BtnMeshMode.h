#ifndef BTNMESHMODE_H
#define BTNMESHMODE_H

#include <QPushButton>
#include <QMouseEvent>
#include <iostream>

class BtnMeshMode:public QPushButton
{
    Q_OBJECT
public:
    explicit BtnMeshMode(QWidget *parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *event);
private:
    bool isMeshMode{false};
};

#endif // BTNMESHMODE_H
