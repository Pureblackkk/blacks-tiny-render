#include<material.h>

Material::Material(Shader &bindShader) {
    shader = &bindShader;
}