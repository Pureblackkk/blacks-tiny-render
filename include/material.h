#ifndef MATERIAL_H
#define MATERIAL_H

#include <shader.h>

class Material {
    public:
        Shader *shader;
        Material(Shader *bindShader);
        void bindDefaultTexture(TGAImage *defaultTexture);
        TGAImage* getDefaultTexture();
        // TODO: add more material variable

    private:
        TGAImage *defaultTexture;
};

#endif