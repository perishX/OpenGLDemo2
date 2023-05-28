#include "CameraOpenGLWidget.h"

CameraOpenGLWidget::CameraOpenGLWidget(QWidget *parent):QOpenGLWidget{parent}
{

}

void CameraOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    this->cube=new Cube();
//    this->shader=new Shader{"C:\\Users\\73965\\Documents\\OpenGLDemo\\shaders\\shader.vert","C:\\Users\\73965\\Documents\\OpenGLDemo\\shaders\\shader.frag"};
    this->shader=new Shader{"D:\\Qt\\projects\\OpenGLDemo2\\shaders\\shader.vert","D:\\Qt\\projects\\OpenGLDemo2\\shaders\\shader.frag"};
    this->floor=new Floor();
//    this->floorShader=new Shader{"C:\\Users\\73965\\Documents\\OpenGLDemo\\shaders\\floorShader.vert","C:\\Users\\73965\\Documents\\OpenGLDemo\\shaders\\floorShader.frag"};
    this->floorShader=new Shader{"D:\\Qt\\projects\\OpenGLDemo2\\shaders\\floorShader.vert","D:\\Qt\\projects\\OpenGLDemo2\\shaders\\floorShader.frag"};
    this->model=new Model{"D:\\Qt\\projects\\OpenGLDemo2\\models\\nanosuit\\nanosuit.obj"};
    this->viewer.moveTo(glm::vec3{4,1,5});
    this->viewer.rotationTo(glm::vec2{0,-135});
}

void CameraOpenGLWidget::resizeGL(int w, int h){
    std::cout<<w<<" "<<h<<std::endl;
    this->g_width=w;
    this->g_height=h;
}

void CameraOpenGLWidget::paintGL(){
    glViewport(0,0,g_width,g_height);

    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//    glm::mat4 model = glm::mat4{1.0f};
    glm::mat4 model = glm::scale(this->modelMatrix,glm::vec3{0.1});

    glm::mat4 view = glm::mat4{1.0f};
    view = this->viewer.getViewMatrix();
    glm::mat4 perspective = glm::mat4{1.0f};
    perspective = glm::perspective(glm::radians(this->viewer.getFov()), static_cast<float>(this->g_width) / static_cast<float>(this->g_height), 0.1f, 100.0f);

    glUseProgram(this->shader->ID);
    this->shader->setMatrix4f("model", 1, glm::value_ptr(model));
    this->shader->setMatrix4f("view", 1, glm::value_ptr(view));
    this->shader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
//    this->cube->Draw();
    this->model->Draw(*this->shader,false);

    model = glm::mat4{1.0f};
    glUseProgram(this->floorShader->ID);
    this->floorShader->setMatrix4f("model", 1, glm::value_ptr(model));
    this->floorShader->setMatrix4f("view", 1, glm::value_ptr(view));
    this->floorShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
    this->floor->Draw();
//    this->mesh->Draw(*this->shader);
}

void CameraOpenGLWidget::setModelMatrix(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale){
    this->modelMatrix = glm::mat4{1.0f};
    this->modelMatrix = glm::translate(this->modelMatrix,position);
    this->modelMatrix = glm::scale(this->modelMatrix,scale);
    this->modelMatrix = glm::rotate(this->modelMatrix,rotation.x,glm::vec3{1,0,0});
    this->modelMatrix = glm::rotate(this->modelMatrix,rotation.y,glm::vec3{0,1,0});
    this->modelMatrix = glm::rotate(this->modelMatrix,rotation.z,glm::vec3{0,0,1});
    update();
}
