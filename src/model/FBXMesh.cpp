#include <gl/glew.h>
//#include <GLFW/glfw3.h>
#include "FBXMesh.h"

FBXMesh::FBXMesh()
{
//    std::cout << "default" << std::endl;
//    this->vertices = {};
//    this->textures = {};
//    this->indices = {0, 1, 2};

//    Vertex vertex1{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)};
//    Vertex vertex2{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)};
//    Vertex vertex3{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)};
//    this->vertices.push_back(vertex1);
//    this->vertices.push_back(vertex2);
//    this->vertices.push_back(vertex3);

//    setupMesh();
}

FBXMesh::FBXMesh(std::vector<FBXVertex> vertices, std::vector<unsigned int> indices, std::vector<FBXTexture> textures)
{
    this->vertices = vertices;
    this->textures = textures;
    this->indices = indices;
//    for(Vertex& v:this->vertices){
//        std::cout<<v.Position.x<<" "<<v.Position.y<<" "<<v.Position.z<<" || ";
//    }
//    std::cout<<'\n';
//    for(unsigned int i:this->indices){
//        std::cout<<i<<" ";
//    }
//    std::cout<<this->vertices.size()<<" "<<this->indices.size()<<std::endl;
    setupMesh();
}

FBXMesh::~FBXMesh()
{

}

void FBXMesh::setupMesh()
{
    glewInit();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
//    std::cout<<VAO<<" "<<VBO<<" "<<EBO<<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(FBXVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void *)offsetof(FBXVertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void *)offsetof(FBXVertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
//    VAO+=2;
//    VBO-=4;
//    EBO-=4;
}

void FBXMesh::Draw(Shader shader, bool isLineMode)
{
    glewInit();
    unsigned int diffNum = 1;
    unsigned int specNum = 1;
    unsigned int reflNum = 1;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        if (textures[i].type == "texture_diffuse")
        {
            number = std::to_string(diffNum++);
        }
        else if (textures[i].type == "texture_specular")
        {
            number = std::to_string(specNum++);
        }
        else if (textures[i].type == "texture_reflect")
        {
            number = std::to_string(reflNum++);
        }
        shader.setInt((textures[i].type + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    if (isLineMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    glDrawElements(GL_TRIANGLES,this->indices.size(), GL_UNSIGNED_INT, (void*)0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void FBXMesh::deleteMesh(){
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);

    glBindVertexArray(0);

    glDeleteVertexArrays(1,&this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1,&this->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1,&this->EBO);

    this->VAO=0;
    this->VBO=0;
    this->EBO=0;

    this->indices.clear();
    this->vertices.clear();
}
