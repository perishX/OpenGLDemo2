#include "MyPushButton.h"

MyPushButton::MyPushButton(QWidget *parent):QPushButton{parent}
{

}


void MyPushButton::mousePressEvent(QMouseEvent *event){
    std::cout<<"MyPushButton"<<std::endl;
    emit clicked();
}
