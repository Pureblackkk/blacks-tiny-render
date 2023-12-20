#include<rasterizer.h>

void Rasterizer::triangle(
    Vector4f (&clip_vert)[3],
    Shader *shader,
    Buffer<Uint32> *frameBuffer,
    Buffer<float> *depthBuffer
) {
    // Define frame size vector width, height
    Matrix4f viewPortMatrix = Matrix4f::deviceViewPort(
        static_cast<float>(frameBuffer->width()), 
        static_cast<float>(frameBuffer->height())
    );

    // Get view port vertices
    Vector4f view_vert[3] = {
       viewPortMatrix * clip_vert[0],
       viewPortMatrix * clip_vert[1],
       viewPortMatrix * clip_vert[2],
    };
    Vector2f view_vert_xy[3] = {
        Vector2f(view_vert[0].x, view_vert[0].y),
        Vector2f(view_vert[1].x, view_vert[1].y),
        Vector2f(view_vert[2].x, view_vert[2].y)
    };

    // Calculate bounding box xmin, xmax, ymin, ymax,
    Vector4i boundingBox(frameBuffer->width() - 1, 0, frameBuffer->height() - 1, 0);
    Rasterizer::triangleBoundingBox(view_vert_xy, boundingBox, frameBuffer);

    // Define edges ba, cb, ac
    Vector2f edge[3] = {
        view_vert_xy[1] - view_vert_xy[0],
        view_vert_xy[2] - view_vert_xy[1],
        view_vert_xy[0] - view_vert_xy[2],
    };

    // Go through bounding box
    for(int i = boundingBox.x; i <= boundingBox.y; ++i) {
        for(int j = boundingBox.z; j <= boundingBox.w; ++j) {
            // Skip those pixel not in the triangle
            Vector4f area;
            if(!isInsideTriagnle(view_vert_xy, edge, area, Vector2f(i + 0.5, j + 0.5))) continue;
            
            // Get barycentric coordinates
            float barycentricFactor = 1 / area.w;
            area = area * barycentricFactor;

            // Skip pixel based on z-depth buffer
            float zDpeth = Vector4f(
                clip_vert[0].z,
                clip_vert[1].z,
                clip_vert[2].z,
                0.0
            ).dot(area);

            if(zDpeth > depthBuffer->get(i, j) || zDpeth > 1.0) continue;

            // Set shader barycentricFactor
            Vector3f barycentricFactorVec(area.x, area.y, area.z);
            Vector4f color = shader->fragment(barycentricFactorVec);
            Uint32 mappedColor = SD2GUI::mapRGBA(color);

            // Set depth buffer
            depthBuffer->set(i, j, zDpeth);

            // Set frame buffer
            frameBuffer->set(i, j, mappedColor);
        }
    }
}

void Rasterizer::triangleBoundingBox(
    Vector2f (&clip_vert)[3],
    Vector4i &boundingBox,
    Buffer<Uint32>* frameBuffer
) {
    for(int i = 0; i < 3; ++i) {
        // x min
        boundingBox.x = std::min(boundingBox.x, static_cast<int>(clip_vert[i].x));
        // x max
        boundingBox.y = std::max(boundingBox.y, static_cast<int>(clip_vert[i].x));
        // y min
        boundingBox.z = std::min(boundingBox.z, static_cast<int>(clip_vert[i].y));
        // y max
        boundingBox.w = std::max(boundingBox.w, static_cast<int>(clip_vert[i].y));
    }

    boundingBox.x = std::max(boundingBox.x, 0);
    boundingBox.y = std::min(boundingBox.y, frameBuffer->width() - 1);
    boundingBox.z = std::max(boundingBox.z, 0);
    boundingBox.w = std::min(boundingBox.w, frameBuffer->height() - 1);
}

bool Rasterizer::isInsideTriagnle(
    Vector2f (&view_vert)[3],
    Vector2f (&edge)[3], // ba, cb, ac
    Vector4f &crossProduct,
    const Vector2f &point
) {
    Vector2f vec0 = view_vert[0] - point;
    float crossProduct0 = edge[0].cross(vec0);

    Vector2f vec1 = view_vert[1] - point;
    float crossProduct1 = edge[1].cross(vec1);

    Vector2f vec2 = view_vert[2] - point;
    float crossProduct2 = edge[2].cross(vec2);

    // Pass the area value to the vector
    crossProduct.x = crossProduct1; 
    crossProduct.y = crossProduct2;
    crossProduct.z = crossProduct0;
    crossProduct.w = crossProduct0 + crossProduct1 + crossProduct2;

    return (
        crossProduct0 >= 0
        && crossProduct1 >=0
        && crossProduct2 >=0
    ) || (
        crossProduct0 <= 0
        && crossProduct1 <= 0
        && crossProduct2 <=0
    );
}