#ifndef BTNPLAYANDPAUSE_H
#define BTNPLAYANDPAUSE_H

#include <QPushButton>
#include <QMouseEvent>
#include <iostream>

class BTNPlayAndPause:public QPushButton
{
    Q_OBJECT
public:
    explicit BTNPlayAndPause(QWidget *parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *event);
    bool isPlay{true};
private:

};

#endif // BTNPLAYANDPAUSE_H
