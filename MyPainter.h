#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <iostream>

class MyPainter:public QWidget
{
public:
    MyPainter(QWidget *parent=nullptr);
    virtual void paintEvent(QPaintEvent *event);
    void draw(QImage image);
private:
    QImage image{};
};

#endif // MYPAINTER_H
