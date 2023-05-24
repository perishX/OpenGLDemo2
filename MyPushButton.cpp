#include "MyPushButton.h"

MyPushButton::MyPushButton(QWidget *parent)
{

}


void MyPushButton::mousePressEvent(QMouseEvent *event){
    std::cout<<"MyPushButton"<<std::endl;
}
