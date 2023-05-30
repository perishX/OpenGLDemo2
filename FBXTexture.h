#ifndef FBXTEXTURE_H
#define FBXTEXTURE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct FBXTexture
{
    unsigned int id;
    std::string type;
    aiString path;
};

#endif // FBXTEXTURE_H
