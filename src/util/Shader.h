#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    void setInt(const char * name,int value);
    void setFloat(const char * name,float value);
    void setBool(const char * name,bool value);
    void setVector3f(const char * name, int count,const float* value);
    void setVector2f(const char * name, int count,const float* value);
    void setMatrix4f(const char * name, int count,const float* value);
};

#endif // SHADER_H
