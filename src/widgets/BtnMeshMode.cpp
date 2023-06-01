#include "BtnMeshMode.h"

BtnMeshMode::BtnMeshMode(QWidget *parent):QPushButton{parent}{

}
void BtnMeshMode::mousePressEvent(QMouseEvent *event){
    std::cout<<"BtnMeshMode"<<std::endl;
    this->isMeshMode=!this->isMeshMode;
    emit clicked(this->isMeshMode);
}
