#ifndef FBXVERTEX_H
#define FBXVERTEX_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct FBXVertex
{
    glm::vec3 Position{};
    glm::vec3 Normal{};
    glm::vec2 TexCoords{};
    FBXVertex():Position{glm::vec3{0}},Normal{glm::vec3{0}},TexCoords{glm::vec2{0}}{}
    FBXVertex(glm::vec3 p,glm::vec3 n,glm::vec2 t):Position{p},Normal{n},TexCoords{t}{}
};

#endif // FBXVERTEX_H
