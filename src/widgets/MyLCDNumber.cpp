#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent):QLCDNumber{parent}
{

}

void MyLCDNumber::setLCDValue(int value){
    this->display(value);
}
