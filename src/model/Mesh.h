#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"
#include "STBImage.h"

class Mesh
{
private:
public:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;
    Mesh();
    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    void Draw(Shader shader, bool isLineMode = false);
    void setupMesh();
    void deleteMesh();
};

#endif // MESH_H
