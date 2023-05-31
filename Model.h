#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <map>
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
#include "BoneInfo.h"
#include "AssimpGLMHelpers.h"

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
    std::function<void()> infoCallback;

    //animation
    std::map<std::string, BoneInfo> m_BoneInfoMap{};
    int m_BoneCounter{0};
public:
    std::vector<Mesh> meshes{};
    Model();
    Model(std::string path);
    ~Model();
    void loadModel(std::string path,std::function<void(float)> callback=[](float){});
    void Draw(Shader shader, bool isLineMode = false);

    void print();
    void deleteMesh();
    int vertexNum{};
    int triangleNum{};
    int boneNum{};
    void calcNodesSum(aiNode *node,const aiScene *scene);
    void initInfo(std::function<void()> infoCallback);

    //animation
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }
    void SetVertexBoneDataToDefault(Vertex& vertex);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
};

#endif // MODEL_H
