#include <gl/glew.h>
#include "FBXModel.h"

FBXModel::FBXModel()
{
    glewInit();
//    std::cout<<"model default"<<std::endl;
}


FBXModel::FBXModel(std::string path)
{
//    glewInit();
    loadModel(path);
//    std::cout<<"model param"<<std::endl;
}

FBXModel::~FBXModel()
{
}

void FBXModel::Draw(Shader shader, bool isLineMode)
{
//    int count=0;
//    if(!hasModel) return;
    for (FBXMesh& mesh : meshes)
    {
        mesh.Draw(shader, isLineMode);
//        std::cout<<count++<<std::endl;
    }
}

void FBXModel::loadModel(std::string path,std::function<void(float)> callback)
{
//    std::cout<<"model loadModel"<<std::endl;
    glewInit();
//    this->hasModel=true;
    Assimp::Importer import{};
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of("/"));

    this->process=0;
    this->totalNode=0;
    this->calcNodesSum(scene->mRootNode);

    processNode(scene->mRootNode, scene, callback);
}

void FBXModel::processNode(aiNode *node, const aiScene *scene,std::function<void(float)> callback)
{
    // 处理节点所有的网格（如果有的话）
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));

    }
    // 接下来对它的子节点重复这一过程
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, callback);
        ++process;
//        std::cout<<"process: "<<process<<" total: "<<totalNode<<std::endl;
        callback(totalNode==0?1:static_cast<float>(process)/totalNode);
    }
}

FBXMesh FBXModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<FBXVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<FBXTexture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        FBXVertex vertex{};
        // 处理顶点位置、法线和纹理坐标
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.Position = position;

        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.Normal = normal;

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

    // 处理材质
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<FBXTexture> diffuseMaps = loadMaterialTextures(material,
                                                                aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<FBXTexture> specularMaps = loadMaterialTextures(material,
                                                                 aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<FBXTexture> reflectMaps = loadMaterialTextures(material,
                                                                aiTextureType_AMBIENT, "texture_reflect");
        textures.insert(textures.end(), reflectMaps.begin(), reflectMaps.end());
    }

    return FBXMesh(vertices, indices, textures);
}

std::vector<FBXTexture> FBXModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                 std::string typeName)
{

    std::vector<FBXTexture> textures;
    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (FBXTexture t : textures_loaded)
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
//            std::cout << type << " " << str.C_Str() << std::endl;
            FBXTexture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
        }
    }

    return textures;
}

//unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma)
//{

//    std::string filename = directory + "/" + std::string(path);

//    int width, height, nrChannels;
//    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

//    unsigned int texture;
//    glGenTextures(1, &texture);

//    // std::cout << "load image" << std::endl;
//    if (data)
//    {
//        GLenum format;
//        if (nrChannels == 1)
//            format = GL_RED;
//        else if (nrChannels == 3)
//            format = GL_RGB;
//        else if (nrChannels == 4)
//            format = GL_RGBA;

//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////        std::cout << "Success to load texture" << std::endl;
//    }
//    else
//    {
//        std::cerr << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//    return texture;
//}


void FBXModel::print(){
    for(FBXMesh& mesh:this->meshes){
        std::cout<<mesh.vertices.size()<<" "<<mesh.indices.size()<<" "<<mesh.textures.size()<<" "<<mesh.VAO<<" "<<mesh.VBO<<" "<<mesh.EBO<<std::endl;
    }
}

void FBXModel::deleteMesh(){
//    this->hasModel=false;
    for (FBXMesh& mesh : meshes)
    {
        mesh.deleteMesh();
    }
    meshes.clear();
    textures_loaded.clear();
}

void FBXModel::calcNodesSum(aiNode *node){
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ++this->totalNode;
        calcNodesSum(node->mChildren[i]);
    }
}