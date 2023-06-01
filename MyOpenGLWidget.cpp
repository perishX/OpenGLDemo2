#include "MyOpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):QOpenGLWidget{parent}{
//    this->grabKeyboard();

}

void MyOpenGLWidget::resizeEvent(QResizeEvent *event){
    this->g_width=this->width();
    this->g_height=this->height();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event){
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

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event){
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

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        this->grabKeyboard();
    }
    if(event->button()==Qt::RightButton){
        this->lastX=event->x();
        this->lastY=event->y();
    }
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
    }
    if(event->button()==Qt::RightButton){
    }
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::RightButton){
        float xOffset=event->x()-this->lastX;
        float yOffset=this->lastY-event->y();

        this->lastX=event->x();
        this->lastY=event->y();

        this->viewer.updateDirection(xOffset,yOffset);
        update();
    }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event){
    float offset{};
    if(event->delta() > 0){
        offset=-1;
    }else{
        offset=1;
    }
    this->viewer.zoom(offset);
    update();
}

void MyOpenGLWidget::focusInEvent(QFocusEvent *event){
//    std::cout<<"OpenGLWidget focusInEvent"<<std::endl;
    this->grabKeyboard();
//    this->grabMouse();
}
void MyOpenGLWidget::focusOutEvent(QFocusEvent *event){
//    std::cout<<"OpenGLWidget focusOutEvent"<<std::endl;
    this->releaseKeyboard();
//    this->releaseMouse();
}

void MyOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    this->cube=new Cube();
    this->cube2=new Cube();
    this->floor=new Floor();
    this->model=new Model();
    this->shader=new Shader{"C:/Users/73965/Documents/OpenGLDemo/shaders/shader.vert","C:/Users/73965/Documents/OpenGLDemo/shaders/shader.frag"};
    this->floorShader=new Shader{"C:/Users/73965/Documents/OpenGLDemo/shaders/floorShader.vert","C:/Users/73965/Documents/OpenGLDemo/shaders/floorShader.frag"};
    this->modelShaderWithAnimation=new Shader{"C:/Users/73965/Documents/OpenGLDemo/shaders/animationModelShader.vert","C:/Users/73965/Documents/OpenGLDemo/shaders/animationModelShader.frag"};
    this->modelShader=new Shader{"C:/Users/73965/Documents/OpenGLDemo/shaders/modelShader.vert","C:/Users/73965/Documents/OpenGLDemo/shaders/modelShader.frag"};

//    this->shader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/shader.vert","D:/Qt/projects/OpenGLDemo2/shaders/shader.frag"};
//    this->floorShader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/floorShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/floorShader.frag"};
//    this->modelShader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/modelShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/modelShader.frag"};
//    this->modelShaderWithAnimation=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/animationModelShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/animationModelShader.frag"};

    char* buffer;

    if((buffer = _getcwd(NULL, 0)) == NULL)
    {
        std::cerr<<"getcwd error"<<std::endl;
    }
    else
    {
        this->workPath=buffer;
        free(buffer);
    }
    std::cout<<workPath<<std::endl;

//    this->shader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/shader.vert","D:/Qt/projects/OpenGLDemo2/shaders/shader.frag"};
//    this->floorShader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/floorShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/floorShader.frag"};
//    this->modelShader=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/modelShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/modelShader.frag"};
//    this->modelShaderWithAnimation=new Shader{"D:/Qt/projects/OpenGLDemo2/shaders/animationModelShader.vert","D:/Qt/projects/OpenGLDemo2/shaders/animationModelShader.frag"};
}

void MyOpenGLWidget::resizeGL(int w, int h){
    std::cout<<w<<" "<<h<<std::endl;
    this->g_width=w;
    this->g_height=h;
}

void MyOpenGLWidget::paintGL(){
//    std::cout<<"paintGL"<<std::endl;
    glViewport(0,0,g_width,g_height);
    glClearColor(0.8f,0.8f,0.8f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4{1.0f};
    glm::mat4 view = glm::mat4{1.0f};
    view = this->viewer.getViewMatrix();
    glm::mat4 perspective = glm::mat4{1.0f};
    perspective = glm::perspective(glm::radians(this->viewer.getFov()), static_cast<float>(this->g_width) / static_cast<float>(this->g_height), 0.1f, 100.0f);

    model= glm::translate(model,glm::vec3{-2,0,0});
    glUseProgram(this->shader->ID);
    this->shader->setMatrix4f("model", 1, glm::value_ptr(model));
    this->shader->setMatrix4f("view", 1, glm::value_ptr(view));
    this->shader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
    this->cube->Draw();

    if(this->showMesh){
        model = glm::mat4{1.0f};
        glUseProgram(this->floorShader->ID);
        this->floorShader->setMatrix4f("model", 1, glm::value_ptr(model));
        this->floorShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->floorShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        this->floor->Draw();
    }

    this->setModelMatrix();
    model = this->modelMatrix;


    if(needLoad){
        this->isLoaded=false;
        this->needLoad=false;
        QProgressDialog *progressDlg=new QProgressDialog;
//        progressDlg->setWindowModality(Qt::WindowModal);
        progressDlg->setMinimumDuration(0);
        progressDlg->setWindowTitle("Please Wait...");
        progressDlg->setLabelText("Loading...");
//        progressDlg->setCancelButtonText("Cancel");
        progressDlg->setRange(0,100);
        progressDlg->show();
        this->model->deleteMesh();
        this->model->loadModel(this->path,[&](float count){
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout<<"count: "<<count<<std::endl;
            progressDlg->setValue(static_cast<int>(count*100));
            int progress=static_cast<int>(count*100);
            QCoreApplication::processEvents();
            makeCurrent();
            if(progress==100){
                std::cout<<"loaded "<<progress<<std::endl;
                progressDlg->cancel();
                this->isLoaded=true;
            }
        });
        if(this->model->hasAnimation()){
            this->animation=new Animation(this->path,this->model);
            this->animator=new Animator(this->animation);
        }
    }
    if(isLoaded){
        if(this->model->hasAnimation()){
            glUseProgram(this->modelShaderWithAnimation->ID);
            this->modelShaderWithAnimation->setMatrix4f("model", 1, glm::value_ptr(model));
            this->modelShaderWithAnimation->setMatrix4f("view", 1, glm::value_ptr(view));
            this->modelShaderWithAnimation->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
            this->modelShaderWithAnimation->setFloat("material.shininess", 256.f);
            this->modelShaderWithAnimation->setVector3f("viewerPos", 1, glm::value_ptr(this->viewer.Pos));
            this->modelShaderWithAnimation->setVector3f("directionLight.color", 1, glm::value_ptr(this->directionlightColor));
            this->modelShaderWithAnimation->setVector3f("directionLight.direction", 1, glm::value_ptr(this->lightDirection));
            this->modelShaderWithAnimation->setVector3f("directionLight.ambient", 1, glm::value_ptr(this->lightColor * 0.2f));
            this->modelShaderWithAnimation->setVector3f("directionLight.diffuse", 1, glm::value_ptr(this->lightColor * 0.5f));
            this->modelShaderWithAnimation->setVector3f("directionLight.specular", 1, glm::value_ptr(this->lightColor * 1.0f));
            if(this->isPlay){
                this->animator->UpdateAnimation(0.033);
            }else{
                this->animator->UpdateAnimation(0);
            }

            std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
            for (int i = 0; i < transforms.size(); ++i){
                glm::mat4 t=transforms[i];
                std::stringstream ss{};
                ss<<"finalBonesMatrices[" << i << "]";
                this->modelShaderWithAnimation->setMatrix4f(ss.str().c_str(), 1, glm::value_ptr(t));
            }
            this->model->Draw(*this->modelShaderWithAnimation,isMeshMode);
        }else{
            glUseProgram(this->modelShader->ID);
            this->modelShader->setMatrix4f("model", 1, glm::value_ptr(model));
            this->modelShader->setMatrix4f("view", 1, glm::value_ptr(view));
            this->modelShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
            this->modelShader->setFloat("material.shininess", 256.f);
            this->modelShader->setVector3f("viewerPos", 1, glm::value_ptr(this->viewer.Pos));
            this->modelShader->setVector3f("directionLight.color", 1, glm::value_ptr(this->directionlightColor));
            this->modelShader->setVector3f("directionLight.direction", 1, glm::value_ptr(this->lightDirection));
            this->modelShader->setVector3f("directionLight.ambient", 1, glm::value_ptr(this->lightColor * 0.2f));
            this->modelShader->setVector3f("directionLight.diffuse", 1, glm::value_ptr(this->lightColor * 0.5f));
            this->modelShader->setVector3f("directionLight.specular", 1, glm::value_ptr(this->lightColor * 1.0f));
            this->model->Draw(*this->modelShader,isMeshMode);
        }

    }

    update();
//    this->mesh->Draw(*this->shader);
}

void MyOpenGLWidget::setModelMatrix(){
    this->modelMatrix = glm::mat4{1.0f};
    this->modelMatrix = glm::translate(this->modelMatrix,this->position);
    this->modelMatrix = glm::scale(this->modelMatrix,this->scale);
    this->modelMatrix = glm::rotate(this->modelMatrix,this->rotation.x,glm::vec3{1,0,0});
    this->modelMatrix = glm::rotate(this->modelMatrix,this->rotation.y,glm::vec3{0,1,0});
    this->modelMatrix = glm::rotate(this->modelMatrix,this->rotation.z,glm::vec3{0,0,1});
}

void MyOpenGLWidget::setModelAttribute(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale){
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->setModelMatrix();
    this->update();
}

void MyOpenGLWidget::hi(){
//    std::cout<<"hiiiii"<<std::endl;
}

void MyOpenGLWidget::test(){
//    std::cout<<"setea"<<std::endl;
}

void MyOpenGLWidget::loadModel(std::string path){
//    this->models.push_back(Model{path});
    std::cout<<path<<std::endl;
//    std::future<bool> f=std::async(std::launch::deferred,[&](std::string path){
//        std::cout<<std::this_thread::get_id()<<" "<<path<<std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//        this->models.push_back(Model{path});
//        return true;
//    },path);
//    std::cout<<f.get()<<std::endl;
//    std::cout << std::this_thread::get_id() << std::endl;
//    this->model->deleteMesh();
//    update();
//    this->model=new Model{"C:/Users/73965/Documents/OpenGLDemo/models/nanosuit/nanosuit.obj"};
//    this->model->loadModel(path);
//this->models.push_back(Model{"C:/Users/73965/Documents/OpenGLDemo/models/nanosuit/nanosuit.obj"});
    this->needLoad=true;
    this->isLoaded=false;
    this->path=path;
//    std::cout<<"loaded!!! "<<this->models.size()<<std::endl;
//    this->models[this->models.size()-1].print();
    update();
}

bool MyOpenGLWidget::load(std::string path){
    std::cout<<std::this_thread::get_id()<<" "<<path<<std::endl;
    return "hello11";
}

void MyOpenGLWidget::setMeshMode(bool isMeshMode){
    this->isMeshMode=isMeshMode;
    update();
}

void MyOpenGLWidget::displayInfo(){
    int vertexNum{};
    int meshNum{};
    for(Model& m:this->models){
        for(Mesh& mesh:m.meshes){
            vertexNum+=mesh.vertices.size();
            meshNum+=mesh.indices.size()/3;
        }
    }
    std::stringstream ss{};
    ss<<"顶点数："<<vertexNum<<"\n"<<"面数："<<meshNum<<std::endl;

    QMessageBox::about(this,"about",ss.str().c_str());
}

void MyOpenGLWidget::setLightColor(glm::vec3 lightColor){
    this->lightColor=lightColor;
    update();
}

void MyOpenGLWidget::setLightRotation(float rotation){
    glm::mat4 rotateMatrix=glm::mat4{1.0f};
    rotateMatrix=glm::rotate(rotateMatrix,rotation,glm::vec3{0,-1,0});
    glm::vec4 temp{0,-1,1,0};
    temp=rotateMatrix*temp;
    this->lightDirection=glm::vec3{temp.x,temp.y,temp.z};
    update();
}

void MyOpenGLWidget::setView(glm::vec3 position,glm::vec2 rotation){
    this->viewer.setView(position,rotation);
    update();
}

void MyOpenGLWidget::setShowMesh(bool showMesh){
    this->showMesh=showMesh;
    std::cout<<"showMesh: "<<showMesh<<std::endl;
    update();
}

void MyOpenGLWidget::setAnimationStatus(bool isPlay){
    std::cout<<"AnimationStatus "<<isPlay<<std::endl;
    this->isPlay=isPlay;
}

void MyOpenGLWidget::setAnimationProgress(int progress){
    this->animator->setAnimation(static_cast<float>(progress)/100.0f);
}

float MyOpenGLWidget::getAnimationProgress(){
    if(this->model->hasAnimation()){
        return this->animator->getProgress();
    }
    return 0;
}
