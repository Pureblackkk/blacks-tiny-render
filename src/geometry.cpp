#include<iostream>
#include<geometry.h>

int Geometry::nverts() const {
    return verts.size();
}

int Geometry::nfaces() const {
    return facet_vrt.size() / 3;
}

Vector3f Geometry::vert(const int i) const {
    return verts[i];
}

Vector3f Geometry::vert(const int iface, const int nthvert) const {
    return verts[facet_vrt[iface * 3 + nthvert]];
}

Vector3f Geometry::normal(const int iface, const int nthvert) const {
    return norms[facet_nrm[iface * 3 + nthvert]];
}

Vector2f Geometry::uv(const int iface, const int nthvert) const {
    return tex_coord[facet_tex[iface * 3 + nthvert]];
}

void Geometry::print() const {
    std::cout << "Vertices number" << Geometry::nverts() << std::endl;
    std::cout << "Faces number" << Geometry::nfaces() << std::endl;
    return;
}



