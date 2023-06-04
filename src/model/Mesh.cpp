#include <gl/glew.h>
//#include <GLFW/glfw3.h>
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->textures = textures;
    this->indices = indices;
    // setupMesh();
}

Mesh::~Mesh()
{

}

void Mesh::setupMesh()
{
    glewInit();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glEnableVertexAttribArray(6);

    glBindVertexArray(0);

    for(Texture& t:this->textures){
        t.id=TextureToGPU(t.info);
    }

}

void Mesh::Draw(Shader shader, bool isLineMode)
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
    glDrawElements(GL_TRIANGLES,this->indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::deleteMesh(){
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
