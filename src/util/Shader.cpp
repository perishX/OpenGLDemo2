#define GLEW_STATIC
#include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    glewInit();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    int success;
    char info[512];
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << info << '\n';
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << info << '\n';
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cerr << "ERROR::LINK_FAILED\n"
                  << info << "  " << vertexPath << '\n';
    }

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    this->ID = shaderProgram;
}

void Shader::setInt(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::setBool(const char *name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::setFloat(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::setVector3f(const char *name, int count, const float *value)
{
    glUniform3fv(glGetUniformLocation(ID, name), count, value);
}
void Shader::setVector2f(const char *name, int count, const float *value)
{
    glUniform2fv(glGetUniformLocation(ID, name), count, value);
}
void Shader::setMatrix4f(const char *name, int count, const float *value)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), count, GL_FALSE, value);
}
