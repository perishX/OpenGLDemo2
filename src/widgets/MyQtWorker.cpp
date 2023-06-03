#include "MyQtWorker.h"

MyQtWorker* MyQtWorker::myworker=nullptr;

MyQtWorker::MyQtWorker()
{
    myworker=this;
    model=new Model{};
}

void MyQtWorker::processCallback(bool isEnd,float rate){
    if(myworker!=nullptr){
        emit myworker->progress(isEnd,rate,myworker->model);
    }
}
void MyQtWorker::start(std::string path){
    delete myworker->model;
    model=new Model{};
    model->loadModel(path,processCallback);
}
