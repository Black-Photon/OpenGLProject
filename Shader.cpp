#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexLocation;// = new std::string;
    std::string fragmentLocation;// = new std::string;
    readVertexFile(vertexPath, &vertexLocation);
    readFragmentFile(fragmentPath, &fragmentLocation);
    const char* vShaderCode = (vertexLocation).c_str();
    const char* fShaderCode = (fragmentLocation).c_str();

    unsigned int vertex, fragment;
    vertex = createVertexShader(vShaderCode);
    fragment = createFragmentShader(fShaderCode);

    linkShaders(&ID, vertex, fragment);
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::readVertexFile(const char* vertexPath, std::string * vertexCode)
{
    std::ifstream vShaderFile;
    // Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // Close file handlers
        vShaderFile.close();
        // Convert stream into string
        *vertexCode = vShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void Shader::readFragmentFile(const char* fragmentPath, std::string * fragmentCode)
{
    std::ifstream fShaderFile;
    // Ensure ifstream objects can throw exceptions:
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        fShaderFile.open(fragmentPath);
        std::stringstream fShaderStream;
        // Read file's buffer contents into streams
        fShaderStream << fShaderFile.rdbuf();
        // Close file handlers
        fShaderFile.close();
        // Convert stream into string
        *fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void Shader::linkShaders(unsigned int * shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
    int success;
    char infoLog[512];

    // SHADER LINKING
    // Creates a basic program object
    *shaderProgram = glCreateProgram();
    // Attaches a compiled shader object to a program
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    // Links all the shaders in the program together
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram[1], 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::PROGRAM::LINKING_SUCCESS" << std::endl;
    }
}

unsigned int Shader::createVertexShader(const char * vertexShaderSource)
{
    // VERTEX SHADERS
    // Makes an empty vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Replaces the current shader source code with that given by the .vert files
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // Compiles the shader object using source code just given
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    // Gets specific info about an element of a shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        // Returns the error log
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED " << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::VERTEX::COMPILATION_SUCCESS" << std::endl;
    }

    return vertexShader;
}

unsigned int Shader::createFragmentShader(const char * fragmentShaderSource)
{
    // FRAGMENT SHADERS
    int success;
    char infoLog[512];

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::FRAGMENT::COMPILATION_SUCCESS" << std::endl;
    }

    return fragmentShader;
}