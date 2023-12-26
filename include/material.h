#ifndef MATERIAL_H
#define MATERIAL_H

#include <shader.h>
#include <loader.h>
#include <map>
#include <string>

class Material {
    public:
        Shader *shader;
        Material(Shader *bindShader);
        void bindDefaultTexture(Image *defaultTexture);
        void bindTexturesByPathMap(std::map<std::string, std::string> &pathMap);
        Image* getDefaultTexture();
        Image* getNormTexture();
        Image* getAlbedo();
        Image* getMetallic();
        Image* getRoughness();
        void setVariableToShaderUniform();
        // TODO: add more material variable

    private:
        std::map<std::string, Image**> textureConfigMap;
        Image *defaultTexture = nullptr;
        Image *normTexture = nullptr;
        Image *albedo = nullptr;
        Image *metallic = nullptr;
        Image *roughness = nullptr;
};

#endif