#ifndef SPACIALFREEZE_TEXTURE_H
#define SPACIALFREEZE_TEXTURE_H

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

namespace texture {
    /**
     * Generates a texture, registering it to be used
     * @param path Path to texture relative to assets folder
     * @param isPNG Whether the image is a png (has an alpha channel)
     * @return Texture created
     */
    Texture generateTexture(const std::string &path, bool alpha);
}

#endif //SPACIALFREEZE_TEXTURE_H
