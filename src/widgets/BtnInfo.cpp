#include "BtnInfo.h"

BtnInfo::BtnInfo(QWidget *parent):QPushButton{parent}{

}
void BtnInfo::mousePressEvent(QMouseEvent *event){
    std::cout<<"BtnInfo"<<std::endl;
    emit clicked();
}
