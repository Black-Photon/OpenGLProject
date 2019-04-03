#ifndef OPENGLPROJECT_SHADER_H
#define OPENGLPROJECT_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    void linkShaders(unsigned int * shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);
    unsigned int createVertexShader(const char * vertexShaderSource);
    unsigned int createFragmentShader(const char * fragmentShaderSource);
    void readVertexFile(const char *vertexPath, std::string * vertexCode);
    void readFragmentFile(const char *fragmentPath, std::string * fragmentCode);
};

#endif //OPENGLPROJECT_SHADER_H
