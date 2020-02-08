#ifndef SPACIALFREEZE_CUBEMODEL_H
#define SPACIALFREEZE_CUBEMODEL_H

#include "CubeMesh.h"

class CubeModel : public Model {
public:
    CubeMesh mesh;
    void draw(Shader shader) override;
    void setTexture(Texture *tex) {
        mesh.setTexture(tex);
    }
};


#endif //SPACIALFREEZE_CUBEMODEL_H
