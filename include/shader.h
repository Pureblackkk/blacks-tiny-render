#ifndef SHADER_H
#define SHADER_H

#include<vector2.h>
#include<vector3.h>
#include<vector4.h>
#include<matrix4.h>

struct UniformShaderVariable {
    Matrix4f modelViewMatrix;
    Matrix4f projectionMatrix;
    // TODO: add light and other possible global shader variable
};

struct VertexShaderVariable {
    Vector3f vert; // Position per vertex
    Vector3f norm; // Normal per vertex3
    Vector2f tex_coord; // Texture coordinate per vertex
    // TODO: see if need more variable
};

struct FragmentShaderVariable {
    Vector2f tex_coord; // Texture coorindate per pixel
};

class Shader {
    public:
        UniformShaderVariable &uniform;
        virtual Vector4f vertex(VertexShaderVariable &vertexShaderVariable);
        virtual Vector4f fragment(FragmentShaderVariable &fragmentShaderVariable);
};
#endif