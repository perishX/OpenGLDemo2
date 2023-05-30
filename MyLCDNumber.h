#ifndef MYLCDNUMBER_H
#define MYLCDNUMBER_H

#include <QLCDNumber>

class MyLCDNumber:public QLCDNumber
{
public:
    explicit MyLCDNumber(QWidget *parent=nullptr);
    void setLCDValue(int value);
};

#endif // MYLCDNUMBER_H
