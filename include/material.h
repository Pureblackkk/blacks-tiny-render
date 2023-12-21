#ifndef MATERIAL_H
#define MATERIAL_H

#include <shader.h>

class Material {
    public:
        Shader *shader;
        Material(Shader *bindShader);
        void bindDefaultTexture(Image *defaultTexture);
        Image* getDefaultTexture();
        // TODO: add more material variable

    private:
        Image *defaultTexture;
};

#endif