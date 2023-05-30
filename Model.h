#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glm/glm.hpp"
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_STATIC
//#include <stb_image.h>
#include "Mesh.h"
#include "Shader.h"
#include "STBImage.h"

class Model
{
private:
    std::vector<Texture> textures_loaded{};
    std::string directory{};
    void processNode(aiNode *node, const aiScene *scene,std::function<void(float)> callback=[](float){});
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
//    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    bool hasModel{false};
    int process{};
    int totalNode{};
    void calcNodesSum(aiNode *node);
public:
    std::vector<Mesh> meshes{};
    Model();
    Model(std::string path);
    ~Model();
    void loadModel(std::string path,std::function<void(float)> callback=[](float){});
    void Draw(Shader shader, bool isLineMode = false);
    void print();
    void deleteMesh();
    int vertexNum{1};
    int triangleNum{2};
    int boneNum{3};
};

#endif // MODEL_H
