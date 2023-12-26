#include<shader.h>

Vector4f Shader::sample2D(Image *img, const Vector2f uv) {
    Color color = img->get(uv.x * img->get_width(), uv.y * img->get_height());
    Vector4f sampledColor = Vector4f(color.r, color.g, color.b, color.a) * (1 / 255.0f);
    sampledColor.w = 1;
    return sampledColor;
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
            return Shader::sample2D(uniform.defaultTexture, varyingTexCoord);
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
            Vector4f textureColor = Shader::sample2D(uniform.defaultTexture, varyingTexCoord);

            // Mix diffuse color, texture color, specular color
            float rate = specularRatio * specular + diffusionRatio * diffusion;
            Vector4f finalColor = textureColor * (1 - rate) 
                + Vector4f(uniform.lights->front()->color(), 1.0) * rate;

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
    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment(Vector3f &barycentricFactor) override {
            return Vector4f(1.0, 0.0, 0.0, 0.0);
        }
    
    private:

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