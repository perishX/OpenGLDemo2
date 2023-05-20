#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    Shader();
//    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
protected:
private:
    unsigned int ID{};
};

#endif // SHADER_H
