#include "MyLineEditWidget.h"

MyLineEditWidget::MyLineEditWidget(QWidget *parent)
{

}

void MyLineEditWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
//        this->grabKeyboard();
    }
}


void MyLineEditWidget::focusInEvent(QFocusEvent *event){
    std::cout<<"LineEdit focusInEvent"<<std::endl;
    this->grabKeyboard();
//    this->grabMouse();
}
void MyLineEditWidget::focusOutEvent(QFocusEvent *event){
    std::cout<<"LineEdit focusOutEvent "<<this->text().toStdString()<<std::endl;
    this->releaseKeyboard();
//    this->releaseMouse();
//    emit this->hello();
    this->num=this->text().toInt();
}



void MyLineEditWidget::textChanged(QString &text){
    std::cout<<text.toStdString()<<std::endl;
}
