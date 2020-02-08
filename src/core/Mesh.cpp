Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

Mesh::~Mesh() {
    // Deletes VAO and VBO data from memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    addAttribute(3); // Position
    addAttribute(3); // Normal
    addAttribute(2); // Texture
    setAttributes();

    glBindVertexArray(0);
}

void setValue(int i);

void Mesh::draw(Shader &shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    for(int i = 0; i < textures.size(); i++){
        setValue(i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
            shader.setBool("usesNormalMap", true);
        } else {
            std::cout << "Unknown Texture Type " << name << std::endl;
            continue;
        }

        shader.setInt("material." + name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // Default if no specular
    if(specularNr == 1) {
        setValue(31);
        shader.setInt("material.texture_specular1", 31);
        glBindTexture(GL_TEXTURE_2D, core::Data.black.id);
    }

    glActiveTexture(GL_TEXTURE0);

    glCheckError();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glCheckError();
    shader.setBool("usesNormalMap", false);
}


void Mesh::setAttribute(int index, int size, int stride, int start){
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *) (start * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void Mesh::addAttribute(int size){
    attributeSizes.push_back(size);
}

void Mesh::setAttributes(){
    std::vector<int> startPos;
    int sum = 0;
    for(int i : attributeSizes) {
        startPos.push_back(sum);
        sum += i;
    }
    for(int i = 0; i < attributeSizes.size(); i++) {
        int v = attributeSizes.at(i);
        setAttribute(i, v, sum, startPos.at(i));
    }
}

void setValue(int i) {
    switch(i) {
        case 0: glActiveTexture(GL_TEXTURE0);
            break;
        case 1: glActiveTexture(GL_TEXTURE1);
            break;
        case 2: glActiveTexture(GL_TEXTURE2);
            break;
        case 3: glActiveTexture(GL_TEXTURE3);
            break;
        case 4: glActiveTexture(GL_TEXTURE4);
            break;
        case 5: glActiveTexture(GL_TEXTURE5);
            break;
        case 6: glActiveTexture(GL_TEXTURE6);
            break;
        case 7: glActiveTexture(GL_TEXTURE7);
            break;
        case 8: glActiveTexture(GL_TEXTURE8);
            break;
        case 9: glActiveTexture(GL_TEXTURE9);
            break;
        case 10: glActiveTexture(GL_TEXTURE10);
            break;
        case 11: glActiveTexture(GL_TEXTURE11);
            break;
        case 12: glActiveTexture(GL_TEXTURE12);
            break;
        case 13: glActiveTexture(GL_TEXTURE13);
            break;
        case 14: glActiveTexture(GL_TEXTURE14);
            break;
        case 15: glActiveTexture(GL_TEXTURE15);
            break;
        case 16: glActiveTexture(GL_TEXTURE16);
            break;
        case 17: glActiveTexture(GL_TEXTURE17);
            break;
        case 18: glActiveTexture(GL_TEXTURE18);
            break;
        case 19: glActiveTexture(GL_TEXTURE19);
            break;
        case 20: glActiveTexture(GL_TEXTURE20);
            break;
        case 21: glActiveTexture(GL_TEXTURE21);
            break;
        case 22: glActiveTexture(GL_TEXTURE22);
            break;
        case 23: glActiveTexture(GL_TEXTURE23);
            break;
        case 24: glActiveTexture(GL_TEXTURE24);
            break;
        case 25: glActiveTexture(GL_TEXTURE25);
            break;
        case 26: glActiveTexture(GL_TEXTURE26);
            break;
        case 27: glActiveTexture(GL_TEXTURE27);
            break;
        case 28: glActiveTexture(GL_TEXTURE28);
            break;
        case 29: glActiveTexture(GL_TEXTURE29);
            break;
        case 30: glActiveTexture(GL_TEXTURE30);
            break;
        case 31: glActiveTexture(GL_TEXTURE31);
            break;
        default:
            logger::error("Invalid Texture Index " + std::to_string(i));
            break;
    }
}