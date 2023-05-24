#ifndef FLOOR_H
#define FLOOR_H

#include <vector>

class Floor
{
private:
    unsigned int VAO;
    unsigned int VBO;
    std::vector<float> vertices;
    void setupMesh();

public:
    Floor();
    Floor(std::vector<float> vertices);
    void Draw(bool isLineMode = false);
};

#endif // FLOOR_H
