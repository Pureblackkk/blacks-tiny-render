#include<mesh.h>

Mesh::Mesh(Geometry &iGeomerty, Material &imaterial) {
    geo = &iGeomerty;
    material = &imaterial;
}

void Mesh::scale(float scaleX, float scaleY, float scaleZ) {
    scaleMatrix = Matrix4f::scaleMatrix(scaleX, scaleY, scaleZ); 
}

void Mesh::position(float x, float y, float z) {
    translateMatrix = Matrix4f::translateMatrix(x, y, z);
}

void Mesh::rotate(float alpha, float beta, float gamma) {
    rotateMatrix = Matrix4f::rotateMatrix(alpha, beta, gamma);
}

Matrix4f Mesh::modelMatrix() {
    Matrix4f res;
    return scaleMatrix * translateMatrix * rotateMatrix * res;
}