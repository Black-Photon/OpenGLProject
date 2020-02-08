Shader::Shader(std::string vertexPath, std::string fragmentPath) :
    Shader(vertexPath, fragmentPath, "") {}

Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
    if(geometryPath.empty()) usesGeometry = false;

    vertexName = vertexPath;
    fragmentName = fragmentPath;
    geometryName = geometryPath;

    std::string vertexLocation;
    std::string fragmentLocation;
    std::string geometryLocation;
    readVertexFile((core::Path.shaders + "vertex/" + vertexPath).c_str(), &vertexLocation);
    readFragmentFile((core::Path.shaders + "fragment/" + fragmentPath).c_str(), &fragmentLocation);
    if(usesGeometry) readGeometryFile((core::Path.shaders + "geometry/" + geometryPath).c_str(), &geometryLocation);
    const char* vShaderCode = (vertexLocation).c_str();
    const char* fShaderCode = (fragmentLocation).c_str();
    const char* gShaderCode = (geometryLocation).c_str();

    unsigned int vertex, fragment, geometry;
    vertex = createVertexShader(vShaderCode);
    fragment = createFragmentShader(fShaderCode);
    if(usesGeometry) geometry = createGeometryShader(gShaderCode);

    if(usesGeometry) linkShaders(&ID, vertex, fragment, geometry);
    else linkShaders(&ID, vertex, fragment);
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(usesGeometry) glDeleteShader(geometry);
}

void Shader::readVertexFile(const char* vertexPath, std::string * vertexCode) const
{
    readFile(vertexPath, vertexCode, "Vertex");
}

void Shader::readFragmentFile(const char* fragmentPath, std::string * fragmentCode) const
{
    readFile(fragmentPath, fragmentCode, "Fragment");
}

void Shader::readGeometryFile(const char *geometryPath, std::string * geometryCode) const
{
    readFile(geometryPath, geometryCode, "Geometry");
}

void Shader::readFile(const char *path, std::string * code, std::string name) const
{
    std::ifstream shaderFile;
    // Ensure ifstream objects can throw exceptions:
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Open files
        shaderFile.open(path);
        std::stringstream shaderStream;
        // Read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // Close file handlers
        shaderFile.close();
        // Convert stream into string
        *code = shaderStream.str();
    } catch(std::ifstream::failure &e) {
        throw shaderException("Couldn't read " + name + " Shader: " + std::string(path));
    }
}

void Shader::linkShaders(unsigned int * shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
    linkShaders(shaderProgram, vertexShader, fragmentShader, 0);
}

void Shader::linkShaders(unsigned int * shaderProgram, unsigned int vertexShader, unsigned int fragmentShader,
                        unsigned int geometryShader)
{
    int success;
    char infoLog[512];

    // SHADER LINKING
    // Creates a basic program object
    *shaderProgram = glCreateProgram();
    // Attaches a compiled shader3d object to a program
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    if(usesGeometry) glAttachShader(*shaderProgram, geometryShader);
    // Links all the shaders in the program together
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(shaderProgram[1], 512, nullptr, infoLog);
        throw shaderException("Couldn't link Shader Inputs");
    }
}

unsigned int Shader::createVertexShader(const char * vertexShaderSource) const
{
    return createShader(vertexShaderSource, GL_VERTEX_SHADER);
}

unsigned int Shader::createFragmentShader(const char * fragmentShaderSource) const
{
    return createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
}

unsigned int Shader::createGeometryShader(const char * geometryShaderSource) const
{
    return createShader(geometryShaderSource, GL_GEOMETRY_SHADER);
}

unsigned int Shader::createShader(const char * shaderSource, GLenum shaderType) const
{
    std::string name;
    std::string path;
    switch(shaderType) {
        case GL_VERTEX_SHADER:
            name = "Vertex";
            path = vertexName;
            break;
        case GL_FRAGMENT_SHADER:
            name = "Fragment";
            path = fragmentName;
            break;
        case GL_GEOMETRY_SHADER:
            name = "Geometry";
            path = geometryName;
            break;
        default:
            name = "Unknown";
            path = "???";
    }

    int success;
    char infoLog[512];

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        throw shaderException("Couldn't compile " + name + " Shader: \"" + path + "\"");
    }

    return shader;
}

void Shader::use() const
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

void Shader::setVec3(const std::string &name, float v1, float v2, float v3) const
{
    setVec3(name, glm::vec3(v1, v2, v3));
}

void Shader::setVec3(const std::string &name, glm::vec3 vec) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec4(const std::string &name, float v1, float v2, float v3, float v4) const
{
    setVec4(name, glm::vec4(v1, v2, v3, v4));
}

void Shader::setVec4(const std::string &name, glm::vec4 vec) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setLight(const std::string &name, Light light) const
{
    setVec3(name + ".position", light.position);
    setVec3(name + ".colour", light.colour);
    setFloat(name + ".intensity", light.intensity);
}

void Shader::setCamera(const std::string &name, Camera camera) const
{
    setVec3(name + ".viewDir", camera.cameraFront);
    setVec3(name + ".position", camera.cameraPos);
}

void Shader::setCubemapCamera(const std::string &name, Camera camera) const
{
    std::vector<glm::mat4> shadowTransforms = camera.getCubemapTransforms();
//    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 6, GL_FALSE, (float*) &shadowTransforms);
    for (unsigned int i = 0; i < 6; ++i)
        setMat4(name + "[" + std::to_string(i) + "]", shadowTransforms[i]);
}