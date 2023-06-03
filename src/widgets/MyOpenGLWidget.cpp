#include "MyOpenGLWidget.h"

MyOpenGLWidget* MyOpenGLWidget::openglWidget=nullptr;

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent}
{
    this->openglWidget=this;
}

void MyOpenGLWidget::resizeEvent(QResizeEvent *event)
{
    this->g_width = this->width();
    this->g_height = this->height();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
    {
        this->viewer.setForwardFlag(1);
    }
    else if (event->key() == Qt::Key_S)
    {
        this->viewer.setForwardFlag(-1);
    }

    if (event->key() == Qt::Key_D)
    {
        this->viewer.setRightFlag(1);
    }
    else if (event->key() == Qt::Key_A)
    {
        this->viewer.setRightFlag(-1);
    }

    if (event->key() == Qt::Key_Q)
    {
        this->viewer.setUpFlag(1);
    }
    else if (event->key() == Qt::Key_E)
    {
        this->viewer.setUpFlag(-1);
    }
    this->viewer.move();
    update();
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S)
    {
        this->viewer.setForwardFlag(0);
    }

    if (event->key() == Qt::Key_D || event->key() == Qt::Key_A)
    {
        this->viewer.setRightFlag(0);
    }

    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_E)
    {
        this->viewer.setUpFlag(0);
    }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->grabKeyboard();
    }
    if (event->button() == Qt::RightButton)
    {
        this->lastX = event->x();
        this->lastY = event->y();
    }
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
    }
    if (event->button() == Qt::RightButton)
    {
    }
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        float xOffset = event->x() - this->lastX;
        float yOffset = this->lastY - event->y();

        this->lastX = event->x();
        this->lastY = event->y();

        this->viewer.updateDirection(xOffset, yOffset);
        update();
    }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    float offset{};
    if (event->delta() > 0)
    {
        offset = -1;
    }
    else
    {
        offset = 1;
    }
    this->viewer.zoom(offset);
    update();
}

void MyOpenGLWidget::focusInEvent(QFocusEvent *event)
{
    this->grabKeyboard();
}
void MyOpenGLWidget::focusOutEvent(QFocusEvent *event)
{
    this->releaseKeyboard();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    this->cube = new Cube();
    this->floor = new Floor();
    this->model = new Model();

    this->shader = new Shader{"shaders/shader.vert", "shaders/shader.frag"};
    this->floorShader = new Shader{"shaders/floorShader.vert", "shaders/floorShader.frag"};
    this->modelShaderWithAnimation = new Shader{"shaders/animationModelShader.vert", "shaders/animationModelShader.frag"};
    this->modelShader = new Shader{"shaders/modelShader.vert", "shaders/modelShader.frag"};

    this->framebuffer = new FrameBuffer{};
    this->frameBufferShader = new Shader{"shaders/framebufferShader.vert", "shaders/framebufferShader.frag"};

    this->fbo = new QOpenGLFramebufferObject{300, 300};
    this->fbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

    this->progressDlg = new QProgressDialog;
    this->progressDlg->close();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    this->g_width = w;
    this->g_height = h;
}

void MyOpenGLWidget::paintGL()
{
    glViewport(0, 0, g_width, g_height);
    this->paintFBO();
    glBindFramebuffer(GL_FRAMEBUFFER, context()->defaultFramebufferObject());

    this->image = this->fbo->toImage();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 view = glm::mat4{1.0f};
    view = this->viewer.getViewMatrix();
    glm::mat4 perspective = glm::mat4{1.0f};
    perspective = glm::perspective(glm::radians(this->viewer.getFov()), static_cast<float>(this->g_width) / static_cast<float>(this->g_height), 0.1f, 100.0f);

    glUseProgram(this->shader->ID);
    this->shader->setMatrix4f("view", 1, glm::value_ptr(view));
    this->shader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
    this->cube->Draw(this->isMeshMode);

    if (this->showMesh)
    {
        glUseProgram(this->floorShader->ID);
        this->floorShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->floorShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        this->floor->Draw();
    }

    if (isLoaded)
    {
        // if (this->model->hasAnimation())
        // {
        //     glUseProgram(this->modelShaderWithAnimation->ID);
        //     this->modelShaderWithAnimation->setMatrix4f("view", 1, glm::value_ptr(view));
        //     this->modelShaderWithAnimation->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        //     this->model->Draw(*this->modelShaderWithAnimation, isMeshMode);
        // }
        // else
        // {
        //     glUseProgram(this->modelShader->ID);
        //     this->modelShader->setMatrix4f("view", 1, glm::value_ptr(view));
        //     this->modelShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        //     this->model->Draw(*this->modelShader, isMeshMode);
        // }

        glUseProgram(this->modelShader->ID);
        this->modelShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->modelShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        this->model->Draw(*this->modelShader, isMeshMode);
    }

    update();
}

void MyOpenGLWidget::setModelMatrix()
{
    this->modelMatrix = glm::mat4{1.0f};
    this->modelMatrix = glm::translate(this->modelMatrix, this->position);
    this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.x, glm::vec3{1, 0, 0});
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.y, glm::vec3{0, 1, 0});
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.z, glm::vec3{0, 0, 1});
}

void MyOpenGLWidget::setModelAttribute(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->setModelMatrix();
    this->update();
}

void MyOpenGLWidget::loadModel(std::string path)
{
    this->needLoad = true;
    this->isLoaded = false;
    this->path = path;
    update();
}

void MyOpenGLWidget::setMeshMode(bool isMeshMode)
{
    this->isMeshMode = isMeshMode;
    update();
}

void MyOpenGLWidget::setLightColor(glm::vec3 lightColor)
{
    this->lightColor = lightColor;
    update();
}

void MyOpenGLWidget::setLightRotation(float rotation)
{
    glm::mat4 rotateMatrix = glm::mat4{1.0f};
    rotateMatrix = glm::rotate(rotateMatrix, rotation, glm::vec3{0, -1, 0});
    glm::vec4 temp{0, -1, 1, 0};
    temp = rotateMatrix * temp;
    this->lightDirection = glm::vec3{temp.x, temp.y, temp.z};
    update();
}

void MyOpenGLWidget::setView(glm::vec3 position, glm::vec2 rotation)
{
    this->viewer.setView(position, rotation);
    update();
}

void MyOpenGLWidget::setShowMesh(bool showMesh)
{
    this->showMesh = showMesh;
    update();
}

void MyOpenGLWidget::setAnimationStatus(bool isPlay)
{
    this->isPlay = isPlay;
}

void MyOpenGLWidget::setAnimationProgress(int progress)
{
    this->animator->setAnimation(static_cast<float>(progress) / 100.0f);
}

float MyOpenGLWidget::getAnimationProgress()
{
    // if (this->model->hasAnimation())
    // {
    //     return this->animator->getProgress();
    // }
    return 0;
}

void MyOpenGLWidget::paintFBO()
{
    this->fbo->bind();
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4{1.0f};
    glm::mat4 view = glm::mat4{1.0f};
    view = this->cameraWidget->viewer.getViewMatrix();
    glm::mat4 perspective = glm::mat4{1.0f};
    perspective = glm::perspective(glm::radians(this->cameraWidget->viewer.getFov()), static_cast<float>(this->cameraWidget->g_width) / static_cast<float>(this->cameraWidget->g_height), 0.1f, 100.0f);

    model = glm::translate(model, glm::vec3{-2, 0, 0});
    glUseProgram(this->shader->ID);
    this->shader->setMatrix4f("model", 1, glm::value_ptr(model));
    this->shader->setMatrix4f("view", 1, glm::value_ptr(view));
    this->shader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
    this->cube->Draw(this->isMeshMode);

    if (this->showMesh)
    {
        model = glm::mat4{1.0f};
        glUseProgram(this->floorShader->ID);
        this->floorShader->setMatrix4f("model", 1, glm::value_ptr(model));
        this->floorShader->setMatrix4f("view", 1, glm::value_ptr(view));
        this->floorShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        this->floor->Draw();
    }

    model = this->modelMatrix;

    if (needLoad)
    {
        this->isLoaded = false;
        this->needLoad = false;
        this->progressDlg->setMinimumDuration(0);
        this->progressDlg->setWindowTitle("Please Wait...");
        this->progressDlg->setLabelText("Loading...");
        this->progressDlg->setRange(0, 100);
        progressDlg->show();
        this->model->deleteMesh();
        this->loadModelAsync();
        // this->model->loadModel(this->path, [&](float count)
        //                        {
        //          progressDlg->setValue(static_cast<int>(count*100));
        //          int progress=static_cast<int>(count*100);
        //          QCoreApplication::processEvents();
        //          makeCurrent();
        //          if(progress==100){
        //              progressDlg->cancel();
        //              this->isLoaded=true;
        //          } });

        // if (this->model->hasAnimation())
        // {
        //     this->animation = new Animation(this->path, this->model);
        //     this->animator = new Animator(this->animation);
        // }
    }

    if (this->needTrangerData)
    {
        this->needTrangerData = false;
        // this->model->print();
        this->model->transferDataToGPU();
        // this->model->print();
        this->isLoaded = true;
        progressDlg->cancel();
    }

    if (isLoaded)
    {
        // this->model->print();
        // if (this->model->hasAnimation())
        // {
        //     glUseProgram(this->modelShaderWithAnimation->ID);
        //     this->modelShaderWithAnimation->setMatrix4f("model", 1, glm::value_ptr(model));
        //     this->modelShaderWithAnimation->setMatrix4f("view", 1, glm::value_ptr(view));
        //     this->modelShaderWithAnimation->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        //     this->modelShaderWithAnimation->setFloat("material.shininess", 256.f);
        //     this->modelShaderWithAnimation->setVector3f("viewerPos", 1, glm::value_ptr(this->viewer.Pos));
        //     this->modelShaderWithAnimation->setVector3f("directionLight.color", 1, glm::value_ptr(this->directionlightColor));
        //     this->modelShaderWithAnimation->setVector3f("directionLight.direction", 1, glm::value_ptr(this->lightDirection));
        //     this->modelShaderWithAnimation->setVector3f("directionLight.ambient", 1, glm::value_ptr(this->lightColor * 0.2f));
        //     this->modelShaderWithAnimation->setVector3f("directionLight.diffuse", 1, glm::value_ptr(this->lightColor * 0.5f));
        //     this->modelShaderWithAnimation->setVector3f("directionLight.specular", 1, glm::value_ptr(this->lightColor * 1.0f));
        //     if (this->isPlay)
        //     {
        //         this->animator->UpdateAnimation(0.033);
        //     }
        //     else
        //     {
        //         this->animator->UpdateAnimation(0);
        //     }

        //     std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
        //     for (int i = 0; i < transforms.size(); ++i)
        //     {
        //         glm::mat4 t = transforms[i];
        //         std::stringstream ss{};
        //         ss << "finalBonesMatrices[" << i << "]";
        //         this->modelShaderWithAnimation->setMatrix4f(ss.str().c_str(), 1, glm::value_ptr(t));
        //     }
        //     this->model->Draw(*this->modelShaderWithAnimation, isMeshMode);
        // }
        // else
        // {
        //     glUseProgram(this->modelShader->ID);
        //     this->modelShader->setMatrix4f("model", 1, glm::value_ptr(model));
        //     this->modelShader->setMatrix4f("view", 1, glm::value_ptr(view));
        //     this->modelShader->setMatrix4f("perspective", 1, glm::value_ptr(perspective));
        //     this->modelShader->setFloat("material.shininess", 256.f);
        //     this->modelShader->setVector3f("viewerPos", 1, glm::value_ptr(this->viewer.Pos));
        //     this->modelShader->setVector3f("directionLight.color", 1, glm::value_ptr(this->directionlightColor));
        //     this->modelShader->setVector3f("directionLight.direction", 1, glm::value_ptr(this->lightDirection));
        //     this->modelShader->setVector3f("directionLight.ambient", 1, glm::value_ptr(this->lightColor * 0.2f));
        //     this->modelShader->setVector3f("directionLight.diffuse", 1, glm::value_ptr(this->lightColor * 0.5f));
        //     this->modelShader->setVector3f("directionLight.specular", 1, glm::value_ptr(this->lightColor * 1.0f));
        //     this->model->Draw(*this->modelShader, isMeshMode);
        // }

        model = glm::mat4{1.0f};
        model = glm::scale(model, glm::vec3{0.1, 0.1, 0.1});
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
        // std::cout<<"sadsa"<<std::endl;
        this->model->Draw(*this->modelShader, isMeshMode);
        // std::cout<<"sad123515sa"<<std::endl;
    }

    this->fbo->release();
}

void MyOpenGLWidget::loadModelAsync()
{
    std::thread t{
        &Model::loadModel, this->model, this->path,[](float rate){
//            std::cout<<"rate "<<rate<<std::endl;
                                  int progress=static_cast<int>(rate*100);
//            openglWidget->progressDlg->setValue(progress);

//                      QCoreApplication::processEvents();
//                      makeCurrent();
                      if(progress==100){
//                          progressDlg->cancel();
                          openglWidget->needTrangerData=true;
                      }
        }};
    t.detach();
}

void MyOpenGLWidget::processCallback(float rate){
    std::cout<<"rate!!!! "<<rate<<std::endl;
    emit loadModelProcess(rate);
}
