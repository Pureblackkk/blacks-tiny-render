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
        void position(const Vector3f p) {
            posV = p;
        };
        Vector3f lookat() const {
            return lookV;
        };
        void lookat(const Vector3f l) {
            lookV = l;
        };
        Vector3f up() const {
            return upV;
        };
        void up(const Vector3f u) {
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

class OrthoCamera : public Camera {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float near, float far) {
            projectionMatrix = Matrix4f::orthoProject(left, right, bottom, top, near, far);
        };
};

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(float fov, float aspect, float near, float far) {
            projectionMatrix = Matrix4f::perspectiveProject(fov, aspect, near, far);
        };
};
#endif