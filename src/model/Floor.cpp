#include <gl/glew.h>
#include "Floor.h"

Floor::Floor(std::vector<float> vertices)
{
    this->vertices = vertices;
    setupMesh();
}

Floor::Floor()
{
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
}

void Floor::Draw(bool isLineMode)
{
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
