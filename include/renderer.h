#ifndef RENDERER_H
#define RENDERER_H

#include<scene.h>
#include<camera.h>
#include<buffer.h>

class Renderer {
    public:
        Renderer(int width, int height);
        void render(Scene &scene, Camera &camera);

    private:
        // TODO: check the value type for frame buffer
        Buffer<Vector4f> *frameBuffer;
        Buffer<float> *depthBuffer;
        bool clipFaces(Vector4f (&clip_vert)[3]);
        void homogeneousnDivided(Vector4f (&clip_vert)[3]);
};

#endif