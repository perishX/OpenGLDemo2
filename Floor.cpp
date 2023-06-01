#include <gl/glew.h>
#include "Floor.h"

Floor::Floor(std::vector<float> vertices)
{
    this->vertices = vertices;
    setupMesh();
}

Floor::Floor()
{
//    this->vertices = {
//        // positions
//        -25.0f, 0, -25.0f,
//        -25.0f, 0, 25.0f,

//        25.0f, 0, -25.0f,
//        25.0f, 0, 25.0f,

//        -25.0f, 0, -25.0f,
//        25.0f, 0, -25.0f,

//        -25.0f, 0, 25.0f,
//        25.0f, 0, 25.0f,
//    };
    float x=-bound;
    float z=-bound;
    float step=this->bound*2.0f/(this->lineNum+1);
    for(int i=1;i<=this->lineNum;++i){
        float step=this->bound*2.0f/(this->lineNum+1);
        x += step;
        this->vertices.push_back(x);
        this->vertices.push_back(0);
        this->vertices.push_back(-bound);
        this->vertices.push_back(x);
        this->vertices.push_back(0);
        this->vertices.push_back(bound);
    }
    for(int i=1;i<=this->lineNum;++i){
        z += step;
        this->vertices.push_back(-bound);
        this->vertices.push_back(0);
        this->vertices.push_back(z);
        this->vertices.push_back(bound);
        this->vertices.push_back(0);
        this->vertices.push_back(z);
    }

    setupMesh();
}

void Floor::setupMesh()
{
    glewInit();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0));
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
}

void Floor::Draw(bool isLineMode)
{
//    std::cout<<"line draw"<<std::endl;
    glewInit();
    if (isLineMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, this->vertices.size());
    glBindVertexArray(0);
}
