#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <vector>

class FrameBuffer{
public:
    FrameBuffer();
    unsigned int framebuffer{};
    unsigned int textureColorbuffer{};
    unsigned int rbo{};
    unsigned int VAO{};
    unsigned int VBO{};
    void Draw(bool isLineMode=false);
private:
    std::vector<float> vertices{};
    void setupMesh();
    void setupBuffer();
    int width{700};
    int height{700};
};

#endif