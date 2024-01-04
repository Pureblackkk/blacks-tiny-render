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
    return tex_coords[facet_tex[iface * 3 + nthvert]];
}

Vector3f Geometry::tangent(const int iface) const {
    return facet_tangent[iface];
}

Vector3f Geometry::bitangent(const int iface) const {
    return facet_bitangent[iface];
}

void Geometry::print() const {
    std::cout << "Vertices number" << Geometry::nverts() << std::endl;
    std::cout << "Faces number" << Geometry::nfaces() << std::endl;
    return;
}

void Geometry::calculateTangentAndBITangent() {
    int facesNum = nfaces();
    for (int i = 0; i < facesNum; i++) {
        Vector3f pos0 = vert(i, 0);
        Vector3f pos1 = vert(i, 1);
        Vector3f pos2 = vert(i, 2);
        Vector2f uv0 = uv(i, 0);
        Vector2f uv1 = uv(i, 1);
        Vector2f uv2 = uv(i, 2);

        Vector3f e1 = pos1 - pos0;
        Vector3f e2 = pos2 - pos0;

        float deltaU1 = uv1.x - uv0.x;
        float deltaU2 = uv2.x - uv0.x;
        float deltaV1 = uv1.y - uv0.y;
        float deltaV2 = uv2.y - uv0.y;

        float denomi = deltaV1 * deltaU2 - deltaV2 * deltaU1;

        Vector3f t = e2 * deltaV1 - e1 * deltaV2;
        Vector3f b = e2 * (-deltaU1) + e1 * deltaU2;

        facet_tangent.push_back(t);
        facet_bitangent.push_back(b);
    }
}



