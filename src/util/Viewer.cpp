#include "Viewer.h"

Viewer::Viewer()
{
    updateDirection(0, 0);
}

Viewer::~Viewer()
{
}

void Viewer::setForwardFlag(float flag)
{
    this->forwardFlag = flag;
}

void Viewer::setRightFlag(float flag)
{
    this->rightFlag = flag;
}

void Viewer::setUpFlag(float flag)
{
    this->upFlag = flag;
}

float Viewer::getForwardFlag()
{
    return this->forwardFlag;
}

float Viewer::getRightFlag()
{
    return this->rightFlag;
}

float Viewer::getUpFlag()
{
    return this->upFlag;
}

float Viewer::getFov()
{
    return this->fov;
}

glm::mat4 Viewer::getViewMatrix()
{
    return glm::lookAt(this->Pos, this->Pos + this->Front, this->Up);
}

void Viewer::updateDirection(float yawOffset, float pitchOffset)
{
    this->yaw += yawOffset * 0.1;
    this->pitch += pitchOffset * 0.1;

    glm::vec3 front{};
    front.y = sin(glm::radians(pitch));
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    this->Front = glm::normalize(front);

    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

void Viewer::move()
{
    this->Pos += (this->Front * this->forwardFlag + this->Right * this->rightFlag + this->WorldUp * this->upFlag) * 0.1f;
}

void Viewer::zoom(float offset)
{
    if (this->fov >= 1.f && this->fov <= 45.f)
    {
        this->fov += offset;
    }
    if (this->fov < 1.f)
    {
        this->fov = 1.f;
    }
    if (this->fov > 45.f)
    {
        this->fov = 45.f;
    }
}

void Viewer::moveTo(glm::vec3 position)
{
    this->Pos = position;
    this->updateDirection();
}
void Viewer::rotationTo(glm::vec2 rotation)
{
    this->pitch = rotation.x;
    this->yaw = rotation.y;
    this->updateDirection();
}

void Viewer::setView(glm::vec3 position, glm::vec2 rotation)
{
    this->Pos = position;
    this->pitch = rotation.x;
    this->yaw = rotation.y;
    this->updateDirection();
}

void Viewer::move(float xOffset, float yOffset)
{
    this->Pos += (this->Right * xOffset + this->Up * yOffset) * 0.05f;
}

void Viewer::rotateAround(float pitchOffset, float yawOffset)
{
    glm::mat4 rotationMatix=glm::mat4{1.0f};
    rotationMatix = glm::rotate(rotationMatix, pitchOffset, glm::vec3{1, 0, 0});
    rotationMatix = glm::rotate(rotationMatix, yawOffset, glm::vec3{0, 1, 0});

    glm::vec4 p=glm::vec4{this->Pos.x,this->Pos.y,this->Pos.z,1.0f};
    p=rotationMatix * p;
    this->Pos=p;
}