#ifndef SCENE_H
#define SCENE_H

#include<vector>
#include<mesh.h>

class Scene {
    public:
        void add(Mesh &mesh);
        std::vector<Mesh*>& getMeshes();

    private:
        std::vector<Mesh*> meshes;
};

#endif