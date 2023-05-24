#ifndef CUBE_H
#define CUBE_H
#include <vector>

class Cube
{
private:
    unsigned int VAO;
    unsigned int VBO;
    std::vector<float> vertices;
    void setupMesh();

public:
    Cube();
    Cube(std::vector<float> vertices);
    ~Cube();
    void Draw(bool isLineMode = false);
};

#endif // CUBE_H
