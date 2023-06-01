#include "GameObject.h"

GameObject::GameObject(QWidget* parent):QLabel{parent}
{

}

void GameObject::mousePressEvent(QMouseEvent *event){
    std::cout<<"GameObject"<<std::endl;
}

void GameObject::enterEvent(QEvent *event){
    std::cout<<"enterEvent"<<std::endl;
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::black);
    sample_palette.setColor(QPalette::WindowText, Qt::white);
//    sample_palette.highlight();

    this->setAutoFillBackground(true);
    this->setPalette(sample_palette);
//    this->setText("What ever text");
}

void GameObject::leaveEvent(QEvent *event){
    std::cout<<"leaveEvent"<<std::endl;
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::black);

    this->setAutoFillBackground(true);
    this->setPalette(sample_palette);
}
