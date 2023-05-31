#include "CameraOpenGLWidget.h"

CameraOpenGLWidget::CameraOpenGLWidget(QWidget *parent):QOpenGLWidget{parent}
{

}

void CameraOpenGLWidget::resizeEvent(QResizeEvent *event){
    this->g_width=this->width();
    this->g_height=this->height();
}

void CameraOpenGLWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        this->viewer.setForwardFlag(1);
    }else if(event->key()==Qt::Key_S){
        this->viewer.setForwardFlag(-1);
    }

    if(event->key()==Qt::Key_D){
       this->viewer.setRightFlag(1);
    }else if(event->key()==Qt::Key_A){
        this->viewer.setRightFlag(-1);
    }

    if(event->key()==Qt::Key_Q){
        this->viewer.setUpFlag(1);
    }else if(event->key()==Qt::Key_E){
        this->viewer.setUpFlag(-1);
    }
    this->viewer.move();
    update();
}

void CameraOpenGLWidget::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W || event->key()==Qt::Key_S){
        this->viewer.setForwardFlag(0);
    }

    if(event->key()==Qt::Key_D || event->key()==Qt::Key_A){
        this->viewer.setRightFlag(0);
    }

    if(event->key()==Qt::Key_Q || event->key()==Qt::Key_E){
        this->viewer.setUpFlag(0);
    }
}

void CameraOpenGLWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        this->grabKeyboard();
    }
    if(event->button()==Qt::RightButton){
        this->lastX=event->x();
        this->lastY=event->y();
    }
}

void CameraOpenGLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
    }
    if(event->button()==Qt::RightButton){
    }
}

void CameraOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::RightButton){
        float xOffset=event->x()-this->lastX;
        float yOffset=this->lastY-event->y();

        this->lastX=event->x();
        this->lastY=event->y();

        this->viewer.updateDirection(xOffset,yOffset);
        update();
    }
}

void CameraOpenGLWidget::wheelEvent(QWheelEvent *event){
    float offset{};
    if(event->delta() > 0){
        offset=-1;
    }else{
        offset=1;
    }
    this->viewer.zoom(offset);
    update();
}

void CameraOpenGLWidget::focusInEvent(QFocusEvent *event){
    std::cout<<"OpenGLWidget focusInEvent"<<std::endl;
    this->grabKeyboard();
//    this->grabMouse();
}
void CameraOpenGLWidget::focusOutEvent(QFocusEvent *event){
    std::cout<<"OpenGLWidget focusOutEvent"<<std::endl;
    this->releaseKeyboard();
//    this->releaseMouse();
}

void CameraOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    this->test=new Cube();
    this->testShader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/shader.vert","D:/Qt/projects/OpenGLDemo2/shaders/shader.frag"};

}

void CameraOpenGLWidget::resizeGL(int w, int h){
    std::cout<<w<<" "<<h<<std::endl;
    this->g_width=w;
    this->g_height=h;
}

void CameraOpenGLWidget::paintGL(){
    glViewport(0,0,g_width,g_height);

    glClearColor(0.8f,0.8f,0.8f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4{1.0f};
    glm::mat4 view = glm::mat4{1.0f};
    view = this->viewer.getViewMatrix();
//    glm::mat4 perspective = glm::mat4{1.0f};
//    perspective = glm::perspective(glm::radians(this->viewer.getFov()), static_cast<float>(this->g_width) / static_cast<float>(this->g_height), 0.1f, 100.0f);

//    model= glm::translate(model,glm::vec3{-2,0,0});
////    glUseProgram(this->testShader->ID);
////    this->testShader->setMatrix4f("model", 1, glm::value_ptr(model));
////    this->testShader->setMatrix4f("view", 1, glm::value_ptr(view));
////    this->testShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
////    this->test->Draw();

    if(this->cube!=nullptr&&this->cubeShader!=nullptr){
        glUseProgram(this->cubeShader->ID);
        this->cubeShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->cube->Draw();
//        model= glm::translate(model,glm::vec3{2,0,0});
//        this->cubeShader->setMatrix4f("model", 1, glm::value_ptr(model));
//        this->cube->Draw();
    }
    makeCurrent();

    if(this->floor!=nullptr&&this->floorShader!=nullptr){
        glUseProgram(this->floorShader->ID);
        this->floorShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->floor->Draw();
    }

    if(this->model!=nullptr&&this->modelShader!=nullptr){
        std::cout<<"model"<<std::endl;
        glUseProgram(this->modelShader->ID);
        this->modelShader->setMatrix4f("model",1,glm::value_ptr(model));
        this->model->Draw(*this->modelShader,false);
    }

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


void CameraOpenGLWidget::setContext(Cube* cube,Shader* cubeShader,Floor* floor,Shader* floorShader,Model* model, Shader* modelShader, bool meshMode){
    this->cube=cube;
    this->cubeShader=cubeShader;
    this->floor=floor;
    this->floorShader=floorShader;
    this->model=model;
    this->modelShader=modelShader;
    this->meshMode=meshMode;
    update();
}
