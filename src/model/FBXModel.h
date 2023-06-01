#ifndef FBXMODEL_H
#define FBXMODEL_H

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glm/glm.hpp"
#include "FBXMesh.h"
#include "FBXTexture.h"
#include "FBXVertex.h"
#include "Shader.h"
#include "STBImage.h"

class FBXModel
{
private:
    std::vector<FBXTexture> textures_loaded{};
    std::string directory{};
    void processNode(aiNode *node, const aiScene *scene,std::function<void(float)> callback=[](float){});
    FBXMesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<FBXTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
//    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    bool hasModel{false};
    int process{};
    int totalNode{};
    void calcNodesSum(aiNode *node);
public:
    std::vector<FBXMesh> meshes{};
    FBXModel();
    FBXModel(std::string path);
    ~FBXModel();
    void loadModel(std::string path,std::function<void(float)> callback=[](float){});
    void Draw(Shader shader, bool isLineMode = false);
    void print();
    void deleteMesh();
};
#endif // FBXMODEL_H
