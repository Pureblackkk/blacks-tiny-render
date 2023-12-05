#ifndef ORBITCONTROL_H
#define ORBITCONTROL_H

#include<camera.h>

class OribitControl {
    public:
        OribitControl(Camera &camera);
        void rotate(const Vector2f curPosition, const Vector2i &screeSize);
        void zoom(float deltaIntensity);
        void setPosition(const Vector2f position);
        bool lock();
        void lock(bool locking);
    
    private:
        bool isLocking = true;
        Vector2f prePosition;
        float scrollIntensity = 0.0f;
        Camera *camera;
        Vector3f calculatePositionVector(const Vector2f &position, const Vector2i &screeSize);
};

#endif