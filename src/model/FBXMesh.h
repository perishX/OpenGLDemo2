#ifndef FBXMESH_H
#define FBXMESH_H

#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Shader.h"
#include "FBXVertex.h"
#include "FBXTexture.h"

class FBXMesh
{
private:
    void setupMesh();

public:
    unsigned int VAO, VBO, EBO;
    std::vector<FBXVertex> vertices;
    std::vector<FBXTexture> textures;
    std::vector<unsigned int> indices;
    FBXMesh();
    FBXMesh(std::vector<FBXVertex> vertices, std::vector<unsigned int> indices, std::vector<FBXTexture> textures);
    ~FBXMesh();

    void Draw(Shader shader, bool isLineMode = false);
    void deleteMesh();
};

#endif // FBXMESH_H
