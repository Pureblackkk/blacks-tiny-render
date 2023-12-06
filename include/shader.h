#ifndef SHADER_H
#define SHADER_H

#include<tgaimage.h>
#include<vector2.h>
#include<vector3.h>
#include<vector4.h>
#include<matrix4.h>
#include<light.h>
#include<vector>

struct UniformShaderVariable {
    Matrix4f modelMatrix;
    Matrix4f viewMatrix;
    Matrix4f modelViewMatrix;
    Matrix4f projectionMatrix;
    std::vector<Light*> *lights;
    TGAImage *defaultTexture;
    TGAImage *normTexture;
    // TODO: add light and other possible global shader variable
};

struct VertexShaderVariable {
    Vector3f vert; // Position per vertex
    Vector3f norm; // Normal per vertex
    Vector2f tex_coord; // Texture coordinate per vertex
    // TODO: see if need more variable
};

struct FragmentShaderVariable {
    Vector2f tex_coord; // Texture coorindate per pixel
};

template <typename T>
struct ShaderVarying {
    T data[3];
    int dataPointer = 0;

    void set(T value) {
        data[dataPointer] = value;
        dataPointer = (dataPointer + 1) % 3;
    }

    T getVarying(Vector3f &barycentricFactor) {
        return data[0] * barycentricFactor.x + data[1] * barycentricFactor.y + data[2] * barycentricFactor.z;
    }
}; 

class Shader {
    public:
        Vector3f barycentricFactor;
        UniformShaderVariable uniform;
        virtual ~Shader() {};
        virtual Vector4f vertex(VertexShaderVariable &vertexShaderVariable) = 0;
        virtual Vector4f fragment() = 0;
        static Vector4f sample2D(TGAImage *img, const Vector2f uv);
};

extern Shader *SIMPLE_SHADER;
extern Shader *TEXTURE_SHADER;
extern Shader *BLINNPHONE_SHADER;
#endif