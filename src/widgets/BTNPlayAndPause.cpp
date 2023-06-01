#include "BTNPlayAndPause.h"

BTNPlayAndPause::BTNPlayAndPause(QWidget *parent):QPushButton{parent}
{

}

void BTNPlayAndPause::mousePressEvent(QMouseEvent *event){
    std::cout<<"BTNPlayAndPause"<<std::endl;
    this->isPlay=!this->isPlay;
    this->setText(this->isPlay?"pause":"play");
    emit clicked(this->isPlay);
}
