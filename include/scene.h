#ifndef SCENE_H
#define SCENE_H

#include<mesh.h>
#include<vector>

class Scene {
    public:
        void add(Mesh &mesh);
        void add(Light &light);
        std::vector<Mesh*>& getMeshes();
        std::vector<Light*>* getLights();

    private:
        std::vector<Mesh*> meshes;
        std::vector<Light*> lights;
};

#endif