#include<material.h>

Material::Material(Shader *bindShader) {
    shader = bindShader;
    // Set texture config map
    textureConfigMap["default"] = &defaultTexture;
    textureConfigMap["norm"] = &normTexture;
    textureConfigMap["albedo"] = &albedo;
    textureConfigMap["metallic"] = &metallic;
    textureConfigMap["roughness"] = &roughness;
}

void Material::bindDefaultTexture(Image *idefaultTexture) {
    if (defaultTexture) delete defaultTexture;
    defaultTexture = idefaultTexture;
}

void Material::bindTexturesByPathMap(std::map<std::string, std::string> &pathMap) {
    for (const auto &pair : pathMap) {
        // Compare key with built in key and get corresponding image pointer;
        auto it = textureConfigMap.find(pair.first);

        if (it != textureConfigMap.end()) {
            Image **ptr = it->second;

            // Previous texture exist then delete
            if (*ptr) delete *ptr;

            // Create new one
            Loader::loadTexture(ptr, pair.second);
        } else {
            // Throw erro when key not found
            throw std::runtime_error("Texture name not defined");
        }
    }

    defaultTexture->write_file("./test.tga");
}

Image* Material::getDefaultTexture() {
    return defaultTexture;
}

Image* Material::getNormTexture() {
    return normTexture;
}

Image* Material::getAlbedo() {
    return albedo;
}

Image* Material::getMetallic() {
    return metallic;
}

Image* Material::getRoughness() {
    return roughness;
}

