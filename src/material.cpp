#include<material.h>

Material::Material(Shader *bindShader) {
    shader = bindShader;
}

void Material::bindDefaultTexture(TGAImage *idefaultTexture) {
    defaultTexture = idefaultTexture;
}

TGAImage* Material::getDefaultTexture() {
    return defaultTexture;
}

