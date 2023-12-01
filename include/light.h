#ifndef LIGHT_H
#define LIGHT_H

#include<vector3.h>

enum LightType {
    POINT,
};

class Light {
    public:
        void position(Vector3f iPosition) {
            positionV = iPosition;
        };
        Vector3f position() {
            return positionV;
        };
        void color(Vector3f icolor) {
            colorV = icolor;
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