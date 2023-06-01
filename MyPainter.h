#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <iostream>
#include "Viewer.h"

class MyPainter:public QWidget
{
public:
    MyPainter(QWidget *parent=nullptr);
    virtual void paintEvent(QPaintEvent *event);
    void draw(QImage image);
    Viewer viewer{};
    int g_width{300};
    int g_height{300};
private:
    QImage image{};
    int lastX{};
    int lastY{};
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
};

#endif // MYPAINTER_H
