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
#include <vector>
#include <sstream>
#include <future>
#include <thread>
#include <chrono>
#include <direct.h>
#include "Shader.h"
#include "Cube.h"
#include "Viewer.h"
#include "Mesh.h"
#include "Floor.h"
#include "Model.h"
#include "GlewInit.h"
#include "FBXModel.h"
#include "Animation.h"
#include "Animator.h"
#include "FrameBuffer.h"
#include "CameraOpenGLWidget.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent=nullptr);
    void setModelMatrix();
    void test();
    void loadModel(std::string path);
    void setMeshMode(bool isMeshMode);
    void displayInfo();
    glm::vec3 position{0,0,0};
    glm::vec3 rotation{0,0,0};
    glm::vec3 scale{1,1,1};
    void setModelAttribute(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale);
    glm::vec3 lightColor{1,1,1};
    glm::vec3 lightDirection{1,-1,1};
    void setLightColor(glm::vec3 lightColor);
    void setLightRotation(float rotation);
    void setView(glm::vec3 position,glm::vec2 rotation);
    void setShowMesh(bool showMesh);
    void setAnimationStatus(bool isPlay);
    void setAnimationProgress(int progress);
    float getAnimationProgress();


    Cube* cube;
    Shader* shader;
    Floor* floor;
    Shader* floorShader;
    Model* model;
    Shader* modelShader;
    Shader* modelShaderWithAnimation;
    bool isMeshMode{false};
    bool isLoaded{false};

    CameraOpenGLWidget* cameraWidget;
    // unsigned int framebuffer;
    // unsigned int textureColorbuffer;
    // unsigned int rbo;

    QImage image{};
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

public slots:
    void hi();

private:

    std::string workPath{};
    Cube* cube2;
    Mesh* mesh;
    Viewer viewer{};


    int g_width{700};
    int g_height{700};
    int lastX{};
    int lastY{};
    glm::mat4 modelMatrix{glm::mat4{1.0f}};

    std::vector<Model> models{};

    glm::vec3 directionlightColor{1.0f, 1.0f, 1.0f};
    glm::vec3 directionlightDir{-0.2f, -1.0f, -0.3f};


    bool load(std::string path);

    std::string path{""};
    bool needLoad{false};


    FBXModel* fbxModel;

    bool showMesh{true};

    Animation* animation;
    Animator* animator;


    bool isPlay{true};
//    int progress{0};


    FrameBuffer* framebuffer;
    Shader* frameBufferShader;

    QOpenGLFramebufferObject* fbo;
signals:
};

#endif // MYOPENGLWIDGET_H
