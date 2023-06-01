#ifndef MYLINEEDITWIDGET_H
#define MYLINEEDITWIDGET_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QString>
#include <iostream>

class MyLineEditWidget : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEditWidget(QWidget *parent=nullptr);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    float num{};
    void updateNum();
};

#endif // MYLINEEDITWIDGET_H
