#ifndef GEOMETRY_H
#define GEOMETRY_H

#include<vector2.h>
#include<vector3.h>
#include<vector>

class Geometry {
    public:
        std::vector<Vector3f> verts{};
        std::vector<Vector2f> tex_coords{};
        std::vector<Vector3f> norms{};

        std::vector<int> facet_vrt{};
        std::vector<int> facet_tex{};
        std::vector<int> facet_nrm{};

        std::vector<Vector3f> facet_tangent{};
        std::vector<Vector3f> facet_bitangent{};

        int nverts() const;
        int nfaces() const;
        Vector3f vert(const int i) const;
        Vector3f vert(const int iface, const int nthvert) const;
        Vector3f normal(const int iface, const int nthvert) const;
        Vector2f uv(const int iface, const int nthvert) const;

        Vector3f tangent(const int iface) const;
        Vector3f bitangent(const int iface) const;
        void calculateTangentAndBITangent();
        
        void print() const;
        
};

#endif