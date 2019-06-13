#include "data.cpp"

/**
 * Methods used in Initialisation
 */

namespace core {

    /**
     * Generates a texture, registering it to be used
     * @param texture Location of to put texture reference in
     * @param path Path to texture relative to assets folder
     * @param isPNG Whether the image is a png (has an alpha channel)
     */
    void generateTexture(unsigned int *texture, std::string path, bool isPNG);

    void generateTexture(unsigned int *texture, const std::string path, bool isPNG) {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);

        // Sets the parameters for the texture to use if incorrectly sized
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set's the Mapmap filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        int width, height, nrChannels;
        unsigned char *data = stbi_load((Path.assets + path).c_str(), &width, &height, &nrChannels, 0);

        // Whether it uses alpha depends on whether it is a .png or not
        GLenum useAlpha;
        if (isPNG) {
            useAlpha = GL_RGBA;
        } else {
            useAlpha = GL_RGB;
        }

        if (data) {
            // Target Dimension, Mipmap level, Texture Format, width, height, 0, Format, Data Type, Image
            glTexImage2D(GL_TEXTURE_2D, 0, useAlpha, width, height, 0, useAlpha, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }
}