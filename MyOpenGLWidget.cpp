#include "MyOpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):QOpenGLWidget{parent}{
    this->grabKeyboard();
}

void MyOpenGLWidget::resizeEvent(QResizeEvent *event){
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event){
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event){
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event){
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event){
}

void MyOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    //this->shader=new Shader{"C:/Users/73965/Documents/OpenGLDemo/shaders/shader.vert","C:/Users/73965/Documents/OpenGLDemo/shaders/shader.frag"};
}

void MyOpenGLWidget::resizeGL(int w, int h){
}

void MyOpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
}
