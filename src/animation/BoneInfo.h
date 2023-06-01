#ifndef BONEINFO_H
#define BONEINFO_H

#include <glm/glm.hpp>

struct BoneInfo
{
    int id{};

    glm::mat4 offset=glm::mat4{1.0f};
};

#endif // BONEINFO_H
