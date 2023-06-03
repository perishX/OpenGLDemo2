#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QMessageBox>
#include <QProgressDialog>
#include <QCoreApplication>
#include <QOpenGLFramebufferObject>
#include <QImage>
#include <iostream>
#include <QWidget>
#include <vector>
#include <sstream>
#include <future>
#include <thread>
#include <chrono>
#include <thread>
#include <direct.h>
#include "Shader.h"
#include "Cube.h"
#include "Viewer.h"
#include "Mesh.h"
#include "Floor.h"
#include "Model.h"
#include "Animation.h"
#include "Animator.h"
#include "FrameBuffer.h"
#include "MyPainter.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    void setModelMatrix();
    void loadModel(std::string path);
    void setMeshMode(bool isMeshMode);
    void setModelAttribute(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void setLightColor(glm::vec3 lightColor);
    void setLightRotation(float rotation);
    void setView(glm::vec3 position, glm::vec2 rotation);
    void setShowMesh(bool showMesh);
    void setAnimationStatus(bool isPlay);
    void setAnimationProgress(int progress);
    float getAnimationProgress();

    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};

    glm::vec3 lightColor{1, 1, 1};
    glm::vec3 lightDirection{1, -1, 1};

    Cube *cube;
    Shader *shader;
    Floor *floor;
    Shader *floorShader;
    Model *model;
    Shader *modelShader;
    Shader *modelShaderWithAnimation;
    bool isMeshMode{false};
    bool isLoaded{false};

    QImage image{};
    MyPainter *cameraWidget;

    static MyOpenGLWidget *openglWidget;
    QProgressDialog *progressDlg;
    static void processCallback(float rate);
    bool needTrangerData{false};
    Animation *animation;
    Animator *animator;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
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
    int g_width{700};
    int g_height{700};
    int lastX{};
    int lastY{};
    glm::mat4 modelMatrix{glm::mat4{1.0f}};

    glm::vec3 directionlightColor{1.0f, 1.0f, 1.0f};
    glm::vec3 directionlightDir{-0.2f, -1.0f, -0.3f};

    std::string path{""};
    bool needLoad{false};
    bool showMesh{true};

    bool isPlay{true};

    FrameBuffer *framebuffer;
    Shader *frameBufferShader;

    QOpenGLFramebufferObject *fbo;
    void paintFBO();

    //    void loadModelAsync();

signals:
    void loadModelProcess(float rate);
};

#endif // MYOPENGLWIDGET_H
