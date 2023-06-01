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
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
//    Vertex():Position{glm::vec3{0}},Normal{glm::vec3{0}},TexCoords{glm::vec2{0}},Tangent{glm::vec3{0}},Bitangent{glm::vec3{0}}{}
//    Vertex(glm::vec3 p,glm::vec3 n,glm::vec2 t,glm::vec3 tg,glm::vec3 bt,int m_BoneIDs[],float m_Weights[])
//        :Position{p},Normal{n},TexCoords{t},Tangent{tg},Bitangent{bt}{
//        for(int i=0;i<MAX_BONE_INFLUENCE;++i){
//            this->m_BoneIDs[i]=m_BoneIDs[i];
//            this->m_Weights[i]=m_Weights[i];
//        }
//    }
};

#endif // VERTEX_H
