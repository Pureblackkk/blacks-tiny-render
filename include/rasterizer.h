#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<shader.h>
#include<buffer.h>
#include<algorithm>
#include<sdl2.h>

class Rasterizer {
    public:
        static void triangle(
            Vector4f (&clip_vert)[3],
            Shader *shader,
            Buffer<Uint32> *frameBuffer,
            Buffer<float> *depthBuffer
        );
        
        static void triangleBoundingBox(
            Vector2f (&clip_vert)[3],
            Vector4i &boundingBox,
            Buffer<Uint32>* frameBuffer
        );

        static bool isInsideTriagnle(
            Vector2f (&view_vert)[3],
            Vector2f (&edge)[3],
            Vector4f &crossProduct,
            const Vector2f &point
        );
};
#endif