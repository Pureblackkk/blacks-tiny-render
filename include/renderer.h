#ifndef RENDERER_H
#define RENDERER_H

#include<scene.h>
#include<camera.h>

class Renderer {
    public:
        void render(Scene &scene, Camera &camera);
};

#endif