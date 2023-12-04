#ifndef RENDERER_H
#define RENDERER_H

#include<scene.h>
#include<camera.h>
#include<buffer.h>
#include<sdl2.h>

class Renderer {
    public:
        Renderer(int width, int height);
        ~Renderer();
        void render(Scene &scene, Camera &camera);
        void render(Scene &scene, Camera &camera, std::string outputPath);

    private:
        // TODO: check the value type for frame buffer
        Buffer<Vector4f> *frameBuffer;
        Buffer<float> *depthBuffer;
        Vector2i rSize;
        bool clipFaces(Vector4f (&clip_vert)[3]);
        void homogeneousnDivided(Vector4f (&clip_vert)[3]);
        void pRender(Scene &scene, Camera &camera);
};

#endif