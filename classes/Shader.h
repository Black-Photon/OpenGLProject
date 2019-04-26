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
    // The program ID
    unsigned int ID;

    /**
     * Initialises and builds the shader
     * @param vertexPath Path to vertex shader relative to shaders
     * @param fragmentPath Path to fragment shader relative to shaders
     * @param location Location of shaders path (Use Path.shaders)
     */
    Shader(std::string vertexPath, std::string fragmentPath, std::string location);
    /**
     * Activates the shader as the one being used to draw
     */
    void use();
    /**
     * Sets a boolean uniform to the given value
     * @param name Variable name
     * @param value Boolean value
     */
    void setBool(const std::string &name, bool value) const;
    /**
     * Sets an integer uniform to the given value
     * @param name Variable name
     * @param value Integer value
     */
    void setInt(const std::string &name, int value) const;
    /**
     * Sets a float uniform to the given value
     * @param name Variable name
     * @param value Float value
     */
    void setFloat(const std::string &name, float value) const;

private:
    /**
     * Links the shader programs together into a single program
     * @param shaderProgram Location to store the program ID
     * @param vertexShader ID of Vertex Shader to use
     * @param fragmentShader ID of Fragment Shader to use
     */
    void linkShaders(unsigned int * shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);
    /**
     * Creates a vertex shader from the source code
     * @param vertexShaderSource Vertex Shader Source Code
     * @return Vertex Shader ID
     */
    unsigned int createVertexShader(const char * vertexShaderSource);
    /**
     * Creates a fragment shader from the source code
     * @param fragmentShaderSource Fragment Shader Source Code
     * @return Fragment Shader ID
     */
    unsigned int createFragmentShader(const char * fragmentShaderSource);
    /**
     * Reads a vertex file, storing it as a string
     * @param vertexPath Path to vertex code file
     * @param vertexCode Location to store the source code extracted
     */
    void readVertexFile(const char *vertexPath, std::string * vertexCode);
    /**
     * Reads a fragment file, storing it as a string
     * @param fragmentPath Path to fragment code file
     * @param fragmentCode Location to store the source code extracted
     */
    void readFragmentFile(const char *fragmentPath, std::string * fragmentCode);
};

#endif //OPENGLPROJECT_SHADER_H
