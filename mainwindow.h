#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <sstream>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GlewInit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GlewInit gt{};

private slots:
    void openModel();
    void exit();
    void about();

    void salute();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked(bool isMeshMode);
    void on_pushButton_3_clicked();
};
#endif // MAINWINDOW_H
