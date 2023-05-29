#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setCentralWidget(ui->openGLWidget);
    connect(ui->actionImport,&QAction::triggered,this,&MainWindow::openModel);
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::exit);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::about);

    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
    //"^(-?\d+)(\.\d+)?$"
//    ui->positionX->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->positionY->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->positionZ->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->rotationX->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->rotationY->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->rotationZ->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->scaleX->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->scaleY->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->scaleZ->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));

    ui->openGLWidget->test();
}

void MainWindow::salute(){
    emit ui->positionX->hello();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openModel(){
    std::cout<<"openModel trigger!!!"<<std::endl;
    QString filename = QFileDialog::getOpenFileName(this,tr("选择模型"),tr("C:/Users/73965/Downloads"),tr("*.fbx *.obj"));
    std::string path=filename.toStdString();
    std::cout<<path<<std::endl;
    ui->openGLWidget->loadModel(path);
}

void MainWindow::exit(){
    std::cout<<"exit trigger!!!"<<std::endl;
//    std::cout<<ui->positionX->num<<std::endl;
//    std::cout<<ui->positionY->num<<std::endl;
//    std::cout<<ui->positionZ->num<<std::endl;
}

void MainWindow::about(){
    std::cout<<"about trigger!!!"<<std::endl;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout<<"sadsa"<<std::endl;
    glm::vec3 position{ui->positionX->num,ui->positionY->num,ui->positionZ->num};
    glm::vec3 rotation{ui->rotationX->num,ui->rotationY->num,ui->rotationZ->num};
    glm::vec3 scale{ui->scaleX->num,ui->scaleY->num,ui->scaleZ->num};
    ui->openGLWidget->setModelMatrix(position,rotation,scale);
}
