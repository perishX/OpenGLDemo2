#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <iostream>

class Floor
{
private:
    unsigned int VAO;
    unsigned int VBO;
    std::vector<float> vertices;
    void setupMesh();
    int bound{10};
    int lineNum{19};
public:
    Floor();
    Floor(std::vector<float> vertices);
    void Draw(bool isLineMode = true);
};

#endif // FLOOR_H
