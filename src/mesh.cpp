#include<mesh.h>

Mesh::Mesh(Geometry &iGeomerty, Material &imaterial) {
    geo = &iGeomerty;
    material = &imaterial;
}