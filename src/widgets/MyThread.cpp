#include "MyThread.h"
#include "mainwindow.h"

MyThread::MyThread(MainWindow* mainwindow, QObject* parent):QThread{parent}{
    this->mainwindow=mainwindow;
}
void MyThread::run(){
    MyQtWorker w;
    connect(&w,&MyQtWorker::progress,mainwindow,&MainWindow::updateProgress);
    w.start(this->path);
}
