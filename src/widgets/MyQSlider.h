#ifndef MYQSLIDER_H
#define MYQSLIDER_H

#include <QSlider>
#include <iostream>
#include <QAbstractSlider>


class MyQSlider:public QSlider
{
    Q_OBJECT
public:
    explicit MyQSlider(QWidget* parent=nullptr);
};

#endif // MYQSLIDER_H
