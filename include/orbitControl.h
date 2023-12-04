#ifndef ORBITCONTROL_H
#define ORBITCONTROL_H

#include<camera.h>

class OribitControl {
    public:
        OribitControl(Camera &camera);
        void rotate(const Vector2f &curPosition, const Vector2i &screeSize);
    
    private:
        Vector2f prePosition;
        Camera *camera;
        Vector3f calculatePositionVector(const Vector2f &position, const Vector2i &screeSize);
};

#endif