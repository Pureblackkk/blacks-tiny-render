#include<material.h>

Material::Material(Shader *bindShader) {
    shader = bindShader;
}

void Material::bindDefaultTexture(Image *idefaultTexture) {
    defaultTexture = idefaultTexture;
}

Image* Material::getDefaultTexture() {
    return defaultTexture;
}

