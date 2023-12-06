#include<renderer.h>
#include<displayer.h>
#include<rasterizer.h>

Renderer::Renderer(int width, int height) {
    // Initial frame buffer and depth buffer
    rSize = Vector2i(width, height);
    frameBuffer = new Buffer<Vector4f>(width, height);
    depthBuffer = new Buffer<float>(width, height, 1.0);
}

Renderer::~Renderer() {
    delete frameBuffer;
    delete depthBuffer;
}

// Offline render
void Renderer::render(Scene &scene, Camera &camera, std::string outputPath) {
    // Render meshes
    Renderer::pRender(scene, camera);

    // Output framebuffer to certain path
    Displayer::offlineDraw(outputPath, frameBuffer);
}

// Realtime render
void Renderer::render(Scene &scene, Camera &camera) {
    // Render meshes
    Renderer::pRender(scene, camera);

    // Output framebuffer to gui
    Displayer::realTimeDraw(frameBuffer);

    // Clean the buffer
    frameBuffer->clean();
    depthBuffer->clean(1.0);
}

// Private render method
void Renderer::pRender(Scene &scene, Camera &camera) {
    // Get meshes for render
    std::vector<Mesh*> meshes = scene.getMeshes();

    // Get lights for render
    std::vector<Light*> *lights = scene.getLights();

    // Render meshes 
    for(Mesh* mesh : meshes) {
        // Get mesh geometry and material
        Geometry *geo = mesh->geo;
        Material *material = mesh->material;

        // Set global shader variable
        material->shader->uniform.modelMatrix = mesh->modelMatrix();
        material->shader->uniform.viewMatrix = camera.getViewMatrix();
        material->shader->uniform.modelViewMatrix = camera.getViewMatrix() * mesh->modelMatrix();
        material->shader->uniform.projectionMatrix = camera.getProjectionMatrix();
        material->shader->uniform.defaultTexture = material->getDefaultTexture();
        material->shader->uniform.lights = lights;

        // Loop geometry faces
        const int meshFaces = geo->nfaces();

        for (int i = 0; i < meshFaces; i++) {
            // Initialize vertex shader variable
            VertexShaderVariable vsa;
            Vector4f clip_vert[3];

            // Loop each verteice in this face
            for (int j : {0, 1, 2}) {
                // Set vertex shader variable
                vsa.vert = geo->vert(i, j);
                vsa.tex_coord = geo->uv(i, j);
                vsa.norm = geo->normal(i, j);

                clip_vert[j] = material->shader->vertex(vsa);
            }

            // Clip vertices
            if(clipFaces(clip_vert)) continue;
            
            // Divided by w 
            Renderer::homogeneousnDivided(clip_vert);

            // Rasterization
            Rasterizer::triangle(clip_vert, material->shader, frameBuffer, depthBuffer);
        }
    }
}

bool Renderer::clipFaces(Vector4f (&clip_vert)[3]) {
    int count = 0;

    for(Vector4f vert : clip_vert) {
        bool inside = (-vert.w <= vert.x <= vert.w)
            && (-vert.w <= vert.y <= vert.w)
            && (-vert.w <= vert.z <= vert.w);
        if (!inside) count++;
    }

    return count == 3;
}

void Renderer::homogeneousnDivided(Vector4f (&clip_vert)[3]) {
    for(int i = 0; i < 3; i++) {
        float factor = 1 / clip_vert[i].w;
        clip_vert[i] = clip_vert[i] * factor;
    }
}