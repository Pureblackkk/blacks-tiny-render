#ifndef MESH_H
#define MESH_H

#include<material.h>
#include<geometry.h>

class Mesh {
    public:
        Geometry *geo;
        Material *material;
        Mesh(Geometry &iGeomerty, Material &imaterial);
};
#endif