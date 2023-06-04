#ifndef MYQTWORKER_H
#define MYQTWORKER_H

#include <string>
#include <QObject>
#include <QThread>
#include "Test.h"
#include "Model.h"
#include "Animation.h"

class MyQtWorker:public QObject
{
    Q_OBJECT
public:
    MyQtWorker();
    static void processCallback(bool isEnd,float rate);
    void start(std::string path);
    Model* model;
private:
    static MyQtWorker* myworker;

signals:
    void progress(bool isEnd,float rate, Model* model);
};

#endif // MYQTWORKER_H
