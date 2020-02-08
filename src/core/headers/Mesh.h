#ifndef SPACIALFREEZE_MESH_H
#define SPACIALFREEZE_MESH_H

#include "Shader.h"
#include "texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
    ~Mesh();

    virtual void draw(Shader &shader);
private:
    unsigned int VAO, VBO, EBO;
    std::vector<int> attributeSizes;

    /**
     * Sets an individual attribute manually
     * @param index Which attribute index it uses
     * @param size Size of attribute
     * @param stride Next element distance
     * @param start Start index
     */
    static void setAttribute(int index, int size, int stride, int start);

    /**
     * Adds an attribute to the queue
     * @param size Size of attribute
     */
    void addAttribute(int size);
    /**
     * Sets all attributes using the queue
     */
    void setAttributes();

    void setupMesh();

protected:
    Mesh() = default;
};


#endif //SPACIALFREEZE_MESH_H
