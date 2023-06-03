#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <string>
#include <QThread>
#include <QtCore>
#include <QMutex>
#include "MyQtWorker.h"
#include "Test.h"
#include "Model.h"

class MainWindow;

class MyThread:public QThread
{
    Q_OBJECT
public:
    MyThread(MainWindow* mainwindow, QObject* parent = nullptr);
    std::string path{};
protected:
    MainWindow* mainwindow;
    void run();
};
#endif
