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
    QLineEdit::focusInEvent(event);


}
void MyLineEditWidget::focusOutEvent(QFocusEvent *event){
    std::cout<<"LineEdit focusOutEvent "<<this->text().toStdString()<<std::endl;
    this->releaseKeyboard();
    QLineEdit::focusOutEvent(event);
//    this->releaseMouse();
//    emit this->hello();
    this->num=this->text().toFloat();
}

void MyLineEditWidget::textChanged(QString &text){
    std::cout<<text.toStdString()<<std::endl;
}

void MyLineEditWidget::updateNum(){
    this->num=this->text().toFloat();
}
