#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    setCentralWidget(ui->openGLWidget);
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::openModel);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui->lightColor, &QPushButton::clicked, this, &MainWindow::on_lightColor_clicked);
    connect(ui->lightDir, &QDial::valueChanged, this, &MainWindow::on_dial_valueChanged);
    connect(ui->up, &QPushButton::clicked, this, &MainWindow::on_up_clicked);
    connect(ui->showMesh, &QCheckBox::stateChanged, this, &MainWindow::on_showMesh_stateChanged);
    connect(ui->playAndPause, &QPushButton::clicked, this, &MainWindow::on_playAndPause_clicked);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_valueChanged);
    connect(ui->horizontalSlider, &QSlider::sliderPressed, this, &MainWindow::on_horizontalSlider_sliderPressed);
    connect(ui->horizontalSlider, &QSlider::sliderReleased, this, &MainWindow::on_horizontalSlider_sliderReleased);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &MainWindow::on_horizontalSlider_sliderMoved);
    connect(ui->openGLWidget, &QOpenGLWidget::frameSwapped, this, &MainWindow::on_openGLWidget_frameSwapped);

    ui->lightR->updateNum();
    ui->lightG->updateNum();
    ui->lightB->updateNum();

    ui->openGLWidget->cameraWidget = ui->widget;

    mythread = new MyThread{this};

    this->progressDlg = new QProgressDialog;
    this->progressDlg->setMinimumDuration(0);
    this->progressDlg->setWindowTitle("Please Wait...");
    this->progressDlg->setLabelText("Loading...");
    this->progressDlg->setRange(0, 100);
    this->progressDlg->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openModel()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("选择模型"), tr("C:/Users/73965/Downloads"), tr("*.fbx *.obj *.dae"));
    std::string path = filename.toStdString();
    if(path!=""){
        mythread->path = path;
        this->path=path;
        this->progressDlg->show();
        this->mythread->start();
    }
}

void MainWindow::exit()
{
    std::cout << "exit trigger!!!" << std::endl;
}

void MainWindow::about()
{
    QMessageBox::about(this, "about", "版本：0.1.1\n更新日期：2023/5/29");
}

void MainWindow::on_pushButton_clicked()
{
    glm::vec3 position{ui->positionX->num, ui->positionY->num, ui->positionZ->num};
    glm::vec3 rotation{ui->rotationX->num, ui->rotationY->num, ui->rotationZ->num};
    glm::vec3 scale{ui->scaleX->num, ui->scaleY->num, ui->scaleZ->num};
    ui->openGLWidget->setModelAttribute(position, rotation, scale);
}

void MainWindow::on_pushButton_2_clicked(bool isMeshMode)
{
    ui->openGLWidget->setMeshMode(isMeshMode);
}

void MainWindow::on_lightColor_clicked()
{
    glm::vec3 color{ui->lightR->num / 255.f, ui->lightG->num / 255.f, ui->lightB->num / 255.f};
    ui->openGLWidget->setLightColor(color);
}

void MainWindow::on_dial_valueChanged(int value)
{
    ui->openGLWidget->setLightRotation(value / 180.f * 3.14159);
}

void MainWindow::on_up_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0, 5, 0}, glm::vec2{-89, -90});
}

void MainWindow::on_front_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0, 1, 5}, glm::vec2{0, -90});
}

void MainWindow::on_bottom_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0, -5, 0}, glm::vec2{89, -90});
}

void MainWindow::on_left_clicked()
{
    ui->openGLWidget->setView(glm::vec3{-5, 1, 0}, glm::vec2{0, 0});
}

void MainWindow::on_back_clicked()
{
    ui->openGLWidget->setView(glm::vec3{0, 1, -5}, glm::vec2{0, 90});
}

void MainWindow::on_right_clicked()
{
    ui->openGLWidget->setView(glm::vec3{5, 1, 0}, glm::vec2{0, -180});
}

void MainWindow::on_showMesh_stateChanged(int arg1)
{
    ui->openGLWidget->setShowMesh(arg1 == 0 ? false : true);
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
    ui->widget->draw(ui->openGLWidget->image);

    float progress = ui->openGLWidget->getAnimationProgress();
    int minimum = ui->horizontalSlider->minimum();
    int maximum = ui->horizontalSlider->maximum();
    ui->horizontalSlider->setValue(static_cast<int>(progress * (maximum - minimum)));
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    ui->openGLWidget->setAnimationStatus(false);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    ui->openGLWidget->setAnimationProgress(this->progress);
    ui->openGLWidget->setAnimationStatus(ui->playAndPause->isPlay);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    this->progress = position;
    ui->horizontalSlider->setValue(position);
}

void MainWindow::updateProgress(bool isEnd, float rate, Model *model)
{
    std::cout << "[rate] " << rate << std::endl;
    this->progressDlg->setValue(static_cast<int>(rate * 100));
    if (isEnd)
    {
        this->progressDlg->cancel();

        ui->openGLWidget->model = model;
        if(model->hasAnimation()){
            ui->openGLWidget->animation = new Animation();
            ui->openGLWidget->animation->loadAnimation(this->path, model);
            ui->openGLWidget->animator = new Animator(ui->openGLWidget->animation);
        }
        ui->openGLWidget->needTrangerData = true;
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

        ui->lcdNumber->display(ui->openGLWidget->model->triangleNum);
        ui->lcdNumber_2->display(ui->openGLWidget->model->vertexNum);
        ui->lcdNumber_3->display(ui->openGLWidget->model->GetBoneCount());
    }
}
