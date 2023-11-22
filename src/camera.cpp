#include<camera.h>

class OrthoCamera : public Camera {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float near, float far) {
            projectionMatrix = Matrix4f::orthoProject(left, right, bottom, top, near, far);
        };
};
