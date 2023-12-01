#include<scene.h>

void Scene::add(Mesh &mesh) {
    meshes.push_back(&mesh);
}

void Scene::add(Light &light) {
    lights.push_back(&light);
}

std::vector<Mesh*>& Scene::getMeshes() {
    return meshes;
}

std::vector<Light*>* Scene::getLights() {
    return &lights;
}