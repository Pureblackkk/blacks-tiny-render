#ifndef CAMERA_H
#define CAMERA_H

#include<vector3.h>
#include<vector4.h>
#include<matrix4.h>

class Camera {
    public:
        Vector3f position() const {
            return posV;
        };
        void position(Vector3f p) {
            posV = p;
        };
        Vector3f lookat() const {
            return lookV;
        };
        void lookat(Vector3f l) {
            lookV = l;
        };
        Vector3f up() const {
            return upV;
        };
        void up(Vector3f u) {
            upV = u;
        };
        // Calculate view matrix
        Matrix4f getViewMatrix() {
            return Matrix4f::lookAt(posV, lookV, upV);
        };
        // Calculate projection matrix
        Matrix4f getProjectionMatrix() {
            return projectionMatrix;
        };
        
    protected:
        Vector3f posV;
        Vector3f lookV;
        Vector3f upV;
        Matrix4f viewMatrix;
        Matrix4f projectionMatrix;
};
#endif