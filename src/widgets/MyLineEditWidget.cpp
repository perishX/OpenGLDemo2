#include "MyLineEditWidget.h"

MyLineEditWidget::MyLineEditWidget(QWidget *parent)
{
}

void MyLineEditWidget::focusInEvent(QFocusEvent *event){
    this->grabKeyboard();
    QLineEdit::focusInEvent(event);
}
void MyLineEditWidget::focusOutEvent(QFocusEvent *event){
    this->releaseKeyboard();
    QLineEdit::focusOutEvent(event);
    this->num=this->text().toFloat();
}

void MyLineEditWidget::updateNum(){
    this->num=this->text().toFloat();
}
