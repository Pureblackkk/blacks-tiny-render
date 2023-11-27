#include<shader.h>

class SimpleShader : public Shader {
    public:
        virtual Vector4f vertex(VertexShaderVariable &vertexShaderVariable) {
            Vector4f position(vertexShaderVariable.vert, 1.0);
            return uniform.projectionMatrix * uniform.modelViewMatrix * position;
        }

        virtual Vector4f fragment(FragmentShaderVariable &fragmentShaderVariable) {
            // Return color red with alpha 1.0;
            return Vector4f(1.0, 0.0, 0.0, 1.0);
        }
};