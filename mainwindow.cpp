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
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::on_pushButton_2_clicked);
    connect(ui->lightColor,&QPushButton::clicked,this,&MainWindow::on_lightColor_clicked);
    connect(ui->lightDir,&QDial::valueChanged,this,&MainWindow::on_dial_valueChanged);
    connect(ui->up,&QPushButton::clicked,this,&MainWindow::on_up_clicked);
    connect(ui->showMesh,&QCheckBox::stateChanged,this,&MainWindow::on_showMesh_stateChanged);
    connect(ui->playAndPause,&QPushButton::clicked,this,&MainWindow::on_playAndPause_clicked);
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,&MainWindow::on_horizontalSlider_valueChanged);
    connect(ui->openGLWidget,&QOpenGLWidget::frameSwapped,this,&MainWindow::on_openGLWidget_frameSwapped);
    connect(ui->horizontalSlider,&QSlider::sliderPressed,this,&MainWindow::on_horizontalSlider_sliderPressed);
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,&MainWindow::on_horizontalSlider_sliderReleased);
    connect(ui->horizontalSlider,&QSlider::sliderMoved,this,&MainWindow::on_horizontalSlider_sliderMoved);
//    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::on_lightColor_clicked);
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

//    ui->openGLWidget->test();
//    this->gt=GlewInit();
    ui->lightR->updateNum();
    ui->lightG->updateNum();
    ui->lightB->updateNum();
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
    QString filename = QFileDialog::getOpenFileName(this,tr("选择模型"),tr("C:/Users/73965/Downloads"),tr("*.fbx *.obj *.dae"));
    std::string path=filename.toStdString();
    std::cout<<path<<std::endl;
    ui->openGLWidget->loadModel(path);

    ui->positionX->setText(QString::number(ui->openGLWidget->position.x));
    ui->positionY->setText(QString::number(ui->openGLWidget->position.y));
    ui->positionZ->setText(QString::number(ui->openGLWidget->position.z));
    ui->rotationX->setText(QString::number(ui->openGLWidget->rotation.x));
    ui->rotationY->setText(QString::number(ui->openGLWidget->rotation.y));
    ui->rotationZ->setText(QString::number(ui->openGLWidget->rotation.z));
    ui->scaleX->setText(QString::number(ui->openGLWidget->scale.x));
    ui->scaleY->setText(QString::number(ui->openGLWidget->scale.y));
    ui->scaleZ->setText(QString::number(ui->openGLWidget->scale.z));
    ui->positionX->updateNum();
    ui->positionX->updateNum();
    ui->positionX->updateNum();
    ui->rotationX->updateNum();
    ui->rotationY->updateNum();
    ui->rotationZ->updateNum();
    ui->scaleX->updateNum();
    ui->scaleY->updateNum();
    ui->scaleZ->updateNum();

    std::cout<<"info "<<ui->openGLWidget->model->vertexNum<<" "<<ui->openGLWidget->model->triangleNum<<std::endl;
    ui->openGLWidget->model->initInfo([&](){
        ui->lcdNumber->setLCDValue(ui->openGLWidget->model->triangleNum);
        ui->lcdNumber_2->setLCDValue(ui->openGLWidget->model->vertexNum);
        ui->lcdNumber_3->setLCDValue(ui->openGLWidget->model->boneNum);
    });
}

void MainWindow::exit(){
    std::cout<<"exit trigger!!!"<<std::endl;
//    std::cout<<ui->positionX->num<<std::endl;
//    std::cout<<ui->positionY->num<<std::endl;
//    std::cout<<ui->positionZ->num<<std::endl;
}

void MainWindow::about(){
    std::cout<<"about trigger!!!"<<std::endl;
    QMessageBox::about(this,"about","版本：0.1.1\n更新日期：2023/5/29");
}

void MainWindow::on_pushButton_clicked()
{
//    std::cout<<"sadsa"<<std::endl;
    glm::vec3 position{ui->positionX->num,ui->positionY->num,ui->positionZ->num};
    glm::vec3 rotation{ui->rotationX->num,ui->rotationY->num,ui->rotationZ->num};
    glm::vec3 scale{ui->scaleX->num,ui->scaleY->num,ui->scaleZ->num};
    ui->openGLWidget->setModelAttribute(position,rotation,scale);
}

void MainWindow::on_pushButton_2_clicked(bool isMeshMode)
{
//    std::cout<<"meshmode: "<<isMeshMode<<std::endl;
    ui->openGLWidget->setMeshMode(isMeshMode);
}

void MainWindow::on_pushButton_3_clicked(){
    std::string title{"title"};
    std::string info{"title"};
//    std::cout<<"info: "<<title<<" "<<info<<std::endl;
    ui->openGLWidget->displayInfo();
}

void MainWindow::on_lightColor_clicked()
{
    glm::vec3 color{ui->lightR->num/255.f,ui->lightG->num/255.f,ui->lightB->num/255.f};
    std::cout<<color.x<<" "<<color.y<<" "<<color.z<<std::endl;
    ui->openGLWidget->setLightColor(color);
}

void MainWindow::on_dial_valueChanged(int value)
{
    std::cout<<"dial "<<value<<std::endl;
    ui->openGLWidget->setLightRotation(value/180.f*3.14159);
}


void MainWindow::on_up_clicked()
{
    std::cout<<"on_up_clicked"<<std::endl;
    ui->openGLWidget->setView(glm::vec3{0,5,0},glm::vec2{-89,-90});
}

void MainWindow::on_front_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0,1,5},glm::vec2{0,-90});
}

void MainWindow::on_bottom_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0,-5,0},glm::vec2{89,-90});
}

void MainWindow::on_left_clicked()
{
    ui->openGLWidget->setView(glm::vec3{-5,1,0},glm::vec2{0,0});
}

void MainWindow::on_back_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0,1,-5},glm::vec2{0,90});
}

void MainWindow::on_right_clicked()
{
    ui->openGLWidget->setView(glm::vec3{5,1,0},glm::vec2{0,-180});
}

void MainWindow::on_showMesh_stateChanged(int arg1)
{
//    std::cout<<"on_showMesh_stateChanged "<<arg1<<std::endl;
    ui->openGLWidget->setShowMesh(arg1==0?false:true);
}

void MainWindow::on_playAndPause_clicked(bool checked)
{
    ui->openGLWidget->setAnimationStatus(checked);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    std::cout<<"on_horizontalSlider_valueChanged "<<value<<std::endl;
//    ui->openGLWidget->setAnimationProgress(value);
//    this->progress=value;
}

void MainWindow::on_openGLWidget_frameSwapped()
{
    std::cout<<"on_openGLWidget_frameSwapped"<<std::endl;
    if(!ui->openGLWidget->isLoaded){
        ui->openGLWidget_2->setContext(ui->openGLWidget->cube,ui->openGLWidget->shader,
                                       ui->openGLWidget->floor,ui->openGLWidget->floorShader,
                                       nullptr,nullptr,false);
    }else{
        std::cout<<"isLoaded"<<std::endl;
        bool hasAnimation=ui->openGLWidget->model->hasAnimation();
        ui->openGLWidget_2->setContext(ui->openGLWidget->cube,ui->openGLWidget->shader,
                                       ui->openGLWidget->floor,ui->openGLWidget->floorShader,
                                       ui->openGLWidget->model,
                                       hasAnimation?ui->openGLWidget->modelShaderWithAnimation:ui->openGLWidget->modelShader,false);
    }


    float progress=ui->openGLWidget->getAnimationProgress();
//    std::cout<<"on_openGLWidget_frameSwapped "<<progress<<std::endl;
    int minimum=ui->horizontalSlider->minimum();
    int maximum=ui->horizontalSlider->maximum();
    ui->horizontalSlider->setValue(static_cast<int>(progress*(maximum-minimum)));
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
//    std::cout<<"on_horizontalSlider_sliderPressed "<<std::endl;
    ui->openGLWidget->setAnimationStatus(false);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
//    std::cout<<"on_horizontalSlider_sliderReleased "<<std::endl;
    ui->openGLWidget->setAnimationProgress(this->progress);
    ui->openGLWidget->setAnimationStatus(ui->playAndPause->isPlay);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    std::cout<<"on_horizontalSlider_sliderMoved "<<position<<std::endl;
    this->progress=position;
    ui->horizontalSlider->setValue(position);
}
