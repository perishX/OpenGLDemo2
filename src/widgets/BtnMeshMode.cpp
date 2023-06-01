#include "BtnMeshMode.h"

BtnMeshMode::BtnMeshMode(QWidget *parent):QPushButton{parent}{
}
void BtnMeshMode::mousePressEvent(QMouseEvent *event){
    this->isMeshMode=!this->isMeshMode;
    emit clicked(this->isMeshMode);
}
