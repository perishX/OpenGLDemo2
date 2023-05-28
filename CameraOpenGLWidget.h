#ifndef CAMERAOPENGLWIDGET_H
#define CAMERAOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Cube.h"
#include "Viewer.h"
#include "Mesh.h"
#include "Floor.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit  CameraOpenGLWidget(QWidget *parent=nullptr);
    void setModelMatrix(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale);
    Shader* shader;
    Cube* cube;
    Floor* floor;
    Shader* floorShader;
    Model* model;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();
private:
    Viewer viewer{};
    int g_width{300};
    int g_height{300};
    glm::mat4 modelMatrix{glm::mat4{1.0f}};
signals:
};

#endif // CAMERAOPENGLWIDGET_H
