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
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void textChanged(QString &text);
    int num{};
    void updateNum();
signals:
    void hello();
};

#endif // MYLINEEDITWIDGET_H
