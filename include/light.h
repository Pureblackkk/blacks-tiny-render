#ifndef LIGHT_H
#define LIGHT_H

#include<vector3.h>

enum LightType {
    POINT_LIGHT,
};

class Light {
    public:
        void position(float x, float y, float z) {
            positionV = Vector3f(x, y, z);
        };
        void position(Vector3f iPosition) {
            positionV = iPosition;
        };
        Vector3f position() {
            return positionV;
        };
        void color(Vector3f icolor) {
            colorV = icolor;
        };
        void color(float r, float g, float b) {
            colorV = Vector3f(r, g, b);
        };
        Vector3f color() {
            return colorV;
        };
        LightType getType() const {
            return type;
        };

    protected:
        Vector3f positionV;
        Vector3f colorV;
        LightType type;
};

#endif