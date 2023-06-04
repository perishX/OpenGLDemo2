#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Info.h"

struct Texture
{
    unsigned int id{};
    std::string type{};
    aiString path{};
    Info info{};
};

#endif // TEXTURE_H
