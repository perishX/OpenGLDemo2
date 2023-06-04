#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <iostream>
#include <string>
#include <sstream>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QProgressDialog>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyThread.h"
#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateProgress(bool isEnd,float rate,Model* model);

private:
    Ui::MainWindow *ui;
    int progress{};
    MyThread* mythread;
    QProgressDialog* progressDlg;
    std::string path={};

private slots:
    void openModel();
    void exit();
    void about();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked(bool isMeshMode);
    void on_lightColor_clicked();
    void on_dial_valueChanged(int value);
    void on_up_clicked();
    void on_front_clicked();
    void on_bottom_clicked();
    void on_left_clicked();
    void on_back_clicked();
    void on_right_clicked();
    void on_showMesh_stateChanged(int arg1);
    void on_playAndPause_clicked(bool checked);
    void on_horizontalSlider_valueChanged(int value);
    void on_openGLWidget_frameSwapped();
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_sliderMoved(int position);
};
#endif // MAINWINDOW_H
