#include<shader.h>

Vector4f Shader::sample2D(TGAImage *img, const Vector2f uv) {
    TGAColor color = img->get(uv.x * img->get_width(), uv.y * img->get_height());
    Vector4f sampledColor = Vector4f(color.r, color.g, color.b, color.a) * (1 / 255.0f);
    return sampledColor;
}

class SimpleShader : public Shader {
    public:
        Vector4f vertex(VertexShaderVariable &vertexShaderVariable) override {
            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        Vector4f fragment() override {
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

        Vector4f fragment() override {
            // Get texture_coord
            Vector2f varyingTexCoord = tex_coord.getVarying(barycentricFactor);

            // Get texture color
            return Shader::sample2D(uniform.normalTexture, varyingTexCoord);
        }
};

// Export simple shader
SimpleShader simpleShader;
TextureShader textureShader;

Shader *SIMPLE_SHADER = &simpleShader;
Shader *TEXTURE_SHADER = &textureShader;
