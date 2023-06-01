#include "MyPainter.h"

MyPainter::MyPainter(QWidget *parent):QWidget{parent}
{

}

void MyPainter::paintEvent(QPaintEvent *event){
    std::cout<<"MyPainter"<<std::endl;
    QPainter painter(this);
//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));
    // 绘制直线
//    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));

//    this->image.fill(Qt::black);
    painter.drawImage(QPoint(0,0),this->image);
}


void MyPainter::draw(QImage image){
    this->image=image;
    update();
}
