#include <gl/glew.h>
#include "Model.h"

Model::Model()
{
}

Model::Model(std::string path)
{
    loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader shader, bool isLineMode)
{
    for (Mesh &mesh : meshes)
    {
        mesh.Draw(shader, isLineMode);
    }
}

void Model::loadModel(std::string path, CallbackFun callback)
{
//    glewInit();
    Assimp::Importer import{};
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    std::cout<<"1111 "<<path<<std::endl;
//    callback(true,1);
    directory = path.substr(0, path.find_last_of("/"));
    std::cout<<"2222"<<directory<<std::endl;
//callback(true,1);
    this->process = 0;
    this->totalNode = 0;

    this->vertexNum = 0;
    this->triangleNum = 0;
    this->calcNodesSum(scene->mRootNode, scene);
//    std::cout<<"processNode start"<<std::endl;
    processNode(scene->mRootNode, scene, callback);
//    std::cout<<"processNode end"<<std::endl;
//    this->infoCallback();
    this->animationNum = scene->mNumAnimations;
}

void Model::processNode(aiNode *node, const aiScene *scene, CallbackFun callback)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, callback);
        ++process;
        if (callback != nullptr)
        {
            callback(process>=totalNode, totalNode == 0 ? 1 : static_cast<float>(process) / totalNode);
        }
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{};

        SetVertexBoneDataToDefault(vertex);

        vertex.Position = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);
        vertex.Normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 texCoords;
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = texCoords;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            indices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

     if (mesh->mMaterialIndex >= 0)
     {
         aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
         std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                                 aiTextureType_DIFFUSE, "texture_diffuse");
         textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
         std::vector<Texture> specularMaps = loadMaterialTextures(material,
                                                                  aiTextureType_SPECULAR, "texture_specular");
         textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
         std::vector<Texture> reflectMaps = loadMaterialTextures(material,
                                                                 aiTextureType_AMBIENT, "texture_reflect");
         textures.insert(textures.end(), reflectMaps.begin(), reflectMaps.end());
     }

    this->ExtractBoneWeightForVertices(vertices, mesh, scene);

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                 std::string typeName)
{

    std::vector<Texture> textures;
    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (Texture t : textures_loaded)
        {
            if (t.path == str)
            {
                textures.push_back(t);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id=-1;
            texture.info=getTextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
        }
    }

    return textures;
}

void Model::print()
{
    for (Mesh &mesh : this->meshes)
    {
        std::cout << mesh.vertices.size() << " " << mesh.indices.size() << " " << mesh.textures.size() << " " << mesh.VAO << " " << mesh.VBO << " " << mesh.EBO<<" ";
        for(Texture& t:mesh.textures){
            std::cout<<t.id<<" ";
        }
        std::cout<< std::endl;
    }
}

void Model::deleteMesh()
{
    for (Mesh &mesh : meshes)
    {
        mesh.deleteMesh();
    }
    meshes.clear();
    textures_loaded.clear();
}

void Model::calcNodesSum(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->vertexNum += mesh->mNumVertices;
        this->triangleNum += mesh->mNumFaces;
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ++this->totalNode;
        calcNodesSum(node->mChildren[i], scene);
    }
}

void Model::initInfo(std::function<void()> infoCallback)
{
    this->infoCallback = infoCallback;
}

void Model::SetVertexBoneDataToDefault(Vertex &vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.m_BoneIDs[i] = -1;
        vertex.m_Weights[i] = 0.0f;
    }
}

void Model::ExtractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh *mesh, const aiScene *scene)
{
    auto &boneInfoMap = m_BoneInfoMap;
    int &boneCount = m_BoneCounter;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = boneCount;
            newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID = boneCount;
            boneCount++;
        }
        else
        {
            boneID = boneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}

void Model::SetVertexBoneData(Vertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.m_BoneIDs[i] < 0)
        {
            vertex.m_Weights[i] = weight;
            vertex.m_BoneIDs[i] = boneID;
            break;
        }
    }
}

bool Model::hasAnimation()
{
    return this->animationNum > 0;
}

void Model::transferDataToGPU()
{
    for (Mesh &mesh : meshes)
    {
        mesh.setupMesh();
    }
}

