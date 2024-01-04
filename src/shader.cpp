#include<shader.h>

Vector4f Shader::sample2DRGBA(Image *img, const Vector2f uv) {
    Color color = img->get(uv.x * img->get_width(), uv.y * img->get_height());
    Vector4f sampledColor = Vector4f(color.r, color.g, color.b, color.a) * (1 / 255.0f);
    sampledColor.w = 1;
    return sampledColor;
}

float Shader::sample2DGRAY(Image *img, const Vector2f uv) {
    Color color = img->get(static_cast<int>(uv.x * img->get_width()), static_cast<int>(uv.y * img->get_height()));
    return color.val / 255.0;
}

Vector4f Shader::unpackNormal(Vector4f &rgba) {
    return rgba * 2 - 1;
}

template <typename T>
T Shader::mix(T &x, T &y, float ratio) {
    return x * (1 - ratio) +  y * ratio;
}

class SimpleShader : public Shader {
    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment(Vector3f &barycentricFactor) override {
            // Return color red with alpha 1.0;
            return Vector4f(1.0, 0.0, 0.0, 1.0);
        }
};

class TextureShader : public Shader {
    ShaderVarying<Vector2f> tex_coord;

    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            // Set texture varying
            tex_coord.set(vertexShaderVariable.tex_coord);

            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment(Vector3f &barycentricFactor) override {
            // Get texture_coord
            Vector2f varyingTexCoord = tex_coord.getVarying(barycentricFactor);

            // Get texture color
            return Shader::sample2DRGBA(uniform.defaultTexture, varyingTexCoord);
        }
};

class BlinnPhongShader : public Shader {
    ShaderVarying<Vector2f> tex_coord;
    ShaderVarying<Vector3f> modelPos;
    ShaderVarying<Vector3f> normal;
    float shininess = 16.0;
    float diffusionRatio = 0.1;
    float specularRatio = 0.3;

    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            // Set tex and normal
            tex_coord.set(vertexShaderVariable.tex_coord);

            // Normal in model space
            normal.set(vertexShaderVariable.norm);

            // Position in model
            modelPos.set(vertexShaderVariable.vert);

            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment(Vector3f &barycentricFactor) override {
            Matrix4f modelMatrixInverse = uniform.modelMatrix.inverse();
            
            // Calculate diffusion color
            // Get light position in model space (here only use the first light)
            Vector3f lightPos = uniform.lights->front()->position();
            Vector3f lightModelPos = (modelMatrixInverse * Vector4f(lightPos, 1.0)).vectorThree();

            // Get current pixel position and normal
            Vector3f pixelModelPos = modelPos.getVarying(barycentricFactor);
            Vector3f modelNorm = normal.getVarying(barycentricFactor).normalized();

            Vector3f lightDir = (lightPos - pixelModelPos).normalized();

            // Get diffusion intensity
            float diffusion = diffuseIntensity(lightDir, modelNorm);

            // Calculate specular color
            Vector3f eyeModelPos = (modelMatrixInverse * Vector4f(uniform.eye, 1.0)).vectorThree();
            Vector3f eyeDir = eyeModelPos - pixelModelPos;
            float specular = specularIntensity(lightDir, eyeDir, modelNorm);

            // Get texture color
            Vector2f varyingTexCoord = tex_coord.getVarying(barycentricFactor);
            Vector4f textureColor = Shader::sample2DRGBA(uniform.defaultTexture, varyingTexCoord);

            // Mix diffuse color, texture color, specular color
            float rate = specularRatio * specular + diffusionRatio * diffusion;
            Vector4f finalColor = textureColor * (1 - rate) 
                + Vector4f(uniform.lights->front()->color(), 1.0) * rate;

            // HDR tone mapping
            finalColor = finalColor / (finalColor + Vector4f(1.0));

            return finalColor;
        }
    
    private:
        // Calculate specture intensity
        float specularIntensity(Vector3f &lightDir, Vector3f &eyeDir, Vector3f &normal) {
            Vector3f half = (lightDir + eyeDir).normalized();
            return std::pow(std::max(0.0f, half.dot(normal)), shininess);
        }

        // Calculate diffusion intensity
        float diffuseIntensity(Vector3f &lightDir, Vector3f &normal) {
            return std::max(0.0f, lightDir.dot(normal));
        }
};

class PBRDirectShader : public Shader {
    ShaderVarying<Vector2f> texCoord;
    ShaderVarying<Vector3f> modelPos;
    ShaderVarying<Vector3f> lightPos;
    ShaderVarying<Vector3f> eyePos;
    ShaderVarying<Vector3f> vTagent;
    ShaderVarying<Vector3f> vBitangent;
    ShaderVarying<Vector3f> normal;
    
    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            // Set texture varying
            texCoord.set(vertexShaderVariable.tex_coord);

            // Set position in model space
            modelPos.set(vertexShaderVariable.vert);

            // Set light position in model space
            Vector3f lightPosInModel = uniform.lights->front()->position();
            lightPosInModel = (uniform.modelMatrixInverse * (Vector4f(lightPosInModel, 1.0))).vectorThree();
            lightPos.set(lightPosInModel);

            // Set view position in model space
            Vector3f viewPosInModel = (uniform.modelMatrixInverse * (Vector4f(uniform.eye, 1.0))).vectorThree();
            eyePos.set(viewPosInModel);

            // Calculate norm by normal map
            Vector3f tangent = vertexShaderVariable.tangent;
            Vector3f bitangent = vertexShaderVariable.bitangent;
            Vector3f norm = vertexShaderVariable.norm;

            tangent = (tangent - (norm * norm.dot(tangent))).normalized();
            bitangent = norm.cross(tangent).normalized();



            // Set norm, tagent, bitagent in model space
            normal.set(vertexShaderVariable.norm);
            vTagent.set(tangent);
            vBitangent.set(bitangent);
        
            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment(Vector3f &barycentricFactor) override {
            // Get texture coordinate
            Vector2f texCoordPerPixel = texCoord.getVarying(barycentricFactor);

            // Get model position
            Vector3f modelPosPerPixel = modelPos.getVarying(barycentricFactor);

            // Get model light position
            Vector3f lightPosPerPixel = lightPos.getVarying(barycentricFactor);

            // Get model eye position
            Vector3f eyePosPerPixel = eyePos.getVarying(barycentricFactor);

            // View direciton
            Vector3f viewDir = (eyePosPerPixel - modelPosPerPixel).normalized();

            // Light direction
            Vector3f lightDir = (lightPosPerPixel - modelPosPerPixel).normalized();

            // Half vector
            Vector3f halfV = (viewDir + lightDir).normalized();

            // Get normal
            Vector3f normalPerPixel = normal.getVarying(barycentricFactor).normalized();
            Vector3f tagentPerPixel = vTagent.getVarying(barycentricFactor).normalized();
            Vector3f biTagentPerPixel = vBitangent.getVarying(barycentricFactor).normalized();

            Matrix4f tbn(
                Vector4f(tagentPerPixel.x, biTagentPerPixel.x, normalPerPixel.x, 0.0),
                Vector4f(tagentPerPixel.y, biTagentPerPixel.y, normalPerPixel.y, 0.0),
                Vector4f(tagentPerPixel.z, biTagentPerPixel.z, normalPerPixel.z, 0.0),
                Vector4f(0.0)
            );

            Vector4f normalRGBA = Shader::sample2DRGBA(uniform.normTexture, texCoordPerPixel);
            Vector4f tagentSpaceCoords = Shader::unpackNormal(normalRGBA);
            normalPerPixel = (tbn * tagentSpaceCoords).vectorThree();

            // Metallic 
            float metallic = Shader::sample2DGRAY(uniform.metallic, texCoordPerPixel);

            // Roughness
            float roughness = Shader::sample2DGRAY(uniform.roughness, texCoordPerPixel);

            // ao
            float ao = Shader::sample2DGRAY(uniform.ao, texCoordPerPixel);
            
            // Albedo
            Vector3f albedo = Shader::sample2DRGBA(uniform.albedo, texCoordPerPixel).vectorThree();
            
            // Norm dot view direction and light direction
            float nDotV = std::max(static_cast<float>(0.0), normalPerPixel.dot(viewDir));
            float nDotL = std::max(static_cast<float>(0.0), normalPerPixel.dot(lightDir));

            // Calculate light radiance
            float distance = (lightPosPerPixel - modelPosPerPixel).length();

            float attenuation = 1.0 / (distance * distance);
            Vector3f radiance = uniform.lights->front()->color();

            // Calculate Fresnel term
            // Base albedo as 0.04
            Vector3f f0(0.04);
            f0 = Shader::mix(f0, albedo, metallic);
            
            Vector3f fTerm = fresnelSchlick(f0, std::max(static_cast<float>(0.0), normalPerPixel.dot(halfV)));

            // Calculate normal distribution term
            float distrTerm = distributionGGX(normalPerPixel, halfV, roughness);

            // Calculate geometry distribution temr
            float geoTerm = geometrySmith(nDotV, nDotL, roughness);

            // Get Cook-Torrance brdf
            Vector3f specularNum = fTerm * distrTerm * geoTerm;
            float specularDenom = 4.0 * nDotL * nDotV;
            specularDenom = 1 / std::max(specularDenom, static_cast<float>(0.001));
            Vector3f specular = specularNum * specularDenom;

            // Get Kd
            Vector3f kd = Vector3f(1.0) - f0;
            kd *= 1.0 - metallic;

            // Get diffuse part
            Vector3f diffuse = kd * albedo * (1.0 / M_PI);

            // Calculate pbr color
            Vector3f res = (diffuse + specular) * radiance * nDotL;
            
            // Add ambient light
            res += Vector3f(0.03) * albedo * ao;

            // HDR tone mapping
            res = res / (res + Vector3f(1.0));

            return Vector4f(res, 1.0);
        }
    
    private:
        Vector3f fresnelSchlick(Vector3f f0, float cosTheta) {
            return f0 + (Vector3f(1.0) - f0) * std::pow(1. - cosTheta, 5.);
        }

        float distributionGGX(Vector3f norm, Vector3f halfV, float roughness) {
            float alpha2 = roughness * roughness;
            float nDotH = std::max((float)0.0, norm.dot(halfV));
            float nDotH2 = nDotH * nDotH;

            float num = alpha2;
            float denom = (nDotH2 * (alpha2 - 1.) + 1.);
            denom = M_PI * denom * denom;

            return num / denom;
        }

        float geometrySchlickGGX(float cosTheta, float roughness) {
            float r = roughness + 1.0;
            float k = (r * r) / 8.0;
            float denom = cosTheta * (1 - k) + k;

            return cosTheta / denom;
        }

        float geometrySmith(float nDotV, float nDotL, float roughness) {
            float ggxlight = geometrySchlickGGX(nDotL, roughness);
            float ggxView = geometrySchlickGGX(nDotV, roughness);

            return nDotL * nDotV;
        }
};

// Export simple shader
SimpleShader simpleShader;
TextureShader textureShader;
BlinnPhongShader blinnPhoneShader;
PBRDirectShader pbrDirectShader;

Shader *SIMPLE_SHADER = &simpleShader;
Shader *TEXTURE_SHADER = &textureShader;
Shader *BLINNPHONE_SHADER = &blinnPhoneShader;
Shader *PBR_DIRECT_SHADER = &pbrDirectShader;