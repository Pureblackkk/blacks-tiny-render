#include<scene.h>

void Scene::add(Mesh &mesh) {
    meshes.push_back(&mesh);
}

std::vector<Mesh*>& Scene::getMeshes() {
    return meshes;
}