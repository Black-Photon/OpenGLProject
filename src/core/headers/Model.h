#ifndef SPACIALFREEZE_MODEL_H
#define SPACIALFREEZE_MODEL_H

class Model {
public:
    explicit Model(std::string path);
    virtual void draw(Shader shader);
private:
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<Texture> texturesLoaded;
    std::string directory;
    
    void loadModel(std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);

    glm::vec2 convertAVec2(aiVector3t<float> vec);
    glm::vec3 convertAVec3(aiVector3t<float> vec);

protected:
    Model() = default;
};

/**
 * Indicated an error occurred in a model loading
 */
struct modelLoadingException : public std::exception {
    std::string s;

    explicit modelLoadingException(const std::string &string) {
        s = string;
    }

    const char *what() const noexcept(true) override {
        return s.c_str();
    }
};


#endif //SPACIALFREEZE_MODEL_H
