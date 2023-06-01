#ifndef MYQCHECKBOX_H
#define MYQCHECKBOX_H

#include <QCheckBox>
#include <QMouseEvent>
#include <iostream>

class MyQCheckBox:public QCheckBox
{
public:
    MyQCheckBox(QWidget* parent=nullptr);
};

#endif // MYQCHECKBOX_H
