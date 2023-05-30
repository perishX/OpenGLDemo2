#ifndef MYQDIAL_H
#define MYQDIAL_H

#include <QDial>
#include <iostream>
#include <QAbstractSlider>

class MyQDial:public QDial
{
    Q_OBJECT
public:
    explicit MyQDial(QWidget* parent=nullptr);
};

#endif // MYQDIAL_H
