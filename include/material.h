#ifndef MATERIAL_H
#define MATERIAL_H

#include <shader.h>

class Material {
    public:
        Shader *shader;
        Material(Shader &bindShader);
        // TODO: add more material variable
};

#endif