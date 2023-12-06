#ifndef MESH_H
#define MESH_H

#include<material.h>
#include<geometry.h>

class Mesh {
    public:
        Geometry *geo;
        Material *material;
        Mesh(Geometry &iGeomerty, Material &imaterial);
        void scale(float scaleX, float scaleY, float scaleZ);
        void position(float x, float y, float z);
        void rotate(float alpha, float beta, float gamma);
        Matrix4f modelMatrix();

    private:
        Matrix4f scaleMatrix;
        Matrix4f translateMatrix;
        Matrix4f rotateMatrix;
};
#endif