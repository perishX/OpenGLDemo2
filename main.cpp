#include "mainwindow.h"

#include <QApplication>
//#include <QHBoxLayout>
//#include <QWidget>
//#include "MyOpenGLWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QWidget* window=new QWidget();

//    MyOpenGLWidget* myOpenGLWidget=new MyOpenGLWidget();
//    MyOpenGLWidget* myOpenGLWidget2=new MyOpenGLWidget();

//    QHBoxLayout* layout=new QHBoxLayout(window);
//    layout->addWidget(myOpenGLWidget);
//    layout->addWidget(myOpenGLWidget2);

//    w.setCentralWidget(window);
    w.show();
    return a.exec();
}
