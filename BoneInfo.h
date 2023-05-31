#ifndef BONEINFO_H
#define BONEINFO_H

#include <glm/glm.hpp>

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id{};

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset=glm::mat4{1.0f};

};

#endif // BONEINFO_H
