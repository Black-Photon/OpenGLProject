namespace texture {
    Texture generateTexture(const std::string &path, bool alpha) {
        Texture texture;

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        // Sets the parameters for the texture to use if incorrectly sized
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set's the Mipmap filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glCheckError();
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        // Whether it uses alpha depends on whether it is a .png or not
        GLenum useAlpha;
        if (alpha) {
            useAlpha = GL_RGBA;
        } else {
            useAlpha = GL_RGB;
        }
        useAlpha = GL_RGB;

        if (data) {
            // Target Dimension, Mipmap level, Texture Format, width, height, 0, Format, Data Type, Image
            glTexImage2D(GL_TEXTURE_2D, 0, useAlpha, width, height, 0, useAlpha, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            logger::error("Failed to load texture at " + path);
        }

        stbi_image_free(data);
        return texture;
    }
}