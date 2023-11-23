#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<shader.h>
#include<buffer.h>
#include<algorithm>

class Rasterizer {
    public:
        static void triangle(
            Vector4f (&clip_vert)[3],
            Shader &shader,
            Buffer<uint32_t> *frameBuffer,
            Buffer<float> *depthBuffer
        );
        
        static void triangleBoundingBox(
            Vector2f (&clip_vert)[3],
            Vector4i &boundingBox,
            Buffer<uint32_t>* frameBuffer
        );

        static bool isInsideTriagnle(
            Vector2f (&view_vert)[3],
            Vector2f (&edge)[3],
            const Vector2f &point
        );
};
#endif