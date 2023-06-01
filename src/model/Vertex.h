#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 Position{};
    glm::vec3 Normal{};
    glm::vec2 TexCoords{};
    glm::vec3 Tangent{};
    glm::vec3 Bitangent{};
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

#endif // VERTEX_H
