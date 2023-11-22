#include<renderer.h>

void Renderer::render(Scene &scene, Camera &camera) {
    // Get meshes for render
    std::vector<Mesh*> meshes = scene.getMeshes();

    // Render meshes 
    for(Mesh* mesh : meshes) {
        // Get mesh geometry and material
        Geometry *geo = mesh->geo;
        Material *material = mesh->material;

        // Loop geometry faces
        const int meshFaces = geo->nfaces();
        for (int i = 0; i < meshFaces; i++) {
            // Initialize vertex shader variable
            VertexShaderVariable vsa;
            Vector4f clip_vert[3];

            // Loop each verteice in this face
            for (int j : {0, 1, 2}) {
                // TODO: currently we only need vertices
                vsa.vert = geo->vert(i, j);
                clip_vert[j] = material->shader.vertex(vsa);
            }

            // Clip vertices
        }
    }
}
