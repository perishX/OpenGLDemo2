#ifndef CAMERAOPENGLWIDGET_H
#define CAMERAOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Cube.h"
#include "Viewer.h"
#include "Mesh.h"
#include "Floor.h"
#include "Model.h"
#include "FrameBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit  CameraOpenGLWidget(QWidget *parent=nullptr);
    void setModelMatrix(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale);
    void setContext(FrameBuffer* framebuffer,Shader* framebufferShader);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
private:
    Viewer viewer{};
    int g_width{300};
    int g_height{300};
    int lastX{};
    int lastY{};
    glm::mat4 modelMatrix{glm::mat4{1.0f}};

    Cube* cube;
    Shader* cubeShader;
    Floor* floor;
    Shader* floorShader;
    Model* model;
    Shader* modelShader;
    bool meshMode{false};

    Cube* test;
    Shader* testShader;

    Shader* framebufferShader;
    FrameBuffer* framebuffer;
signals:
};

#endif // CAMERAOPENGLWIDGET_H
