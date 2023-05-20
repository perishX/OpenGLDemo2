#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"


Shader::Shader(){

}

//Shader::Shader(const char *vertexPath, const char *fragmentPath)
//{
//    // 1. 从文件路径中获取顶点/片段着色器
//    std::string vertexCode;
//    std::string fragmentCode;
//    std::ifstream vShaderFile;
//    std::ifstream fShaderFile;
//    // 保证ifstream对象可以抛出异常：
//    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//    try
//    {
//        // 打开文件
//        vShaderFile.open(vertexPath);
//        fShaderFile.open(fragmentPath);
//        std::stringstream vShaderStream, fShaderStream;
//        // 读取文件的缓冲内容到数据流中
//        vShaderStream << vShaderFile.rdbuf();
//        fShaderStream << fShaderFile.rdbuf();
//        // 关闭文件处理器
//        vShaderFile.close();
//        fShaderFile.close();
//        // 转换数据流到string
//        vertexCode = vShaderStream.str();
//        fragmentCode = fShaderStream.str();
//    }
//    catch (std::ifstream::failure e)
//    {
//        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//    }
//    const char *vShaderCode = vertexCode.c_str();
//    const char *fShaderCode = fragmentCode.c_str();

//    int success;
//    char info[512];

//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
//    glCompileShader(vertexShader);
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
//        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
//                  << info << '\n';
//    }
//    else
//    {
//        std::cout << "VERTEX SHADER COMPILE SUCCESS" << '\n';
//    }

//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
//    glCompileShader(fragmentShader);
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
//        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
//                  << info << '\n';
//    }
//    else
//    {
//        std::cout << "FRAGMENT SHADER COMPILE SUCCESS" << '\n';
//    }

//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);

//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success)
//    {
//        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
//        std::cerr << "ERROR::LINK_FAILED\n"
//                  << info << '\n';
//    }
//    else
//    {
//        std::cout << "LINK SUCCESS" << '\n';
//    }

//    glDeleteShader(fragmentShader);
//    glDeleteShader(vertexShader);

//    this->ID = shaderProgram;
//}

Shader::~Shader(){

}

