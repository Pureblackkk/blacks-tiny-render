#ifndef CUBEMAP_H
#define CUBEMAP_H

#include<image.h>
#include<loader.h>

struct Cubemap {
    Image *front; // idx 0
    Image *back; // idx 1
    Image *left; // idx 2
    Image *right; // idx 3
    Image *up; // idx 4
    Image *down; // idx 5 

    Cubemap(
        std::string frontPath, 
        std::string backPath, 
        std::string leftPath, 
        std::string rightPath, 
        std::string upPath, 
        std::string downPath
    ) {
        Loader::loadTexture(&front, frontPath);
        Loader::loadTexture(&back, frontPath);
        Loader::loadTexture(&left, leftPath);
        Loader::loadTexture(&right, rightPath);
        Loader::loadTexture(&up, upPath);
        Loader::loadTexture(&down, downPath);
    };

    Image *getFaces(unsigned int face) {
        switch (face)
        {
            case 0:
                return front;
            case 1:
                return back;
            case 2:
                return left;
            case 3:
                return right;
            case 4:
                return up;
            case 5:
                return down;
            default:
                throw std::runtime_error("wrong cube face map index");
        };
    }

    Vector3f uvToDir(unsigned int face, Vector2f uv) {
        float x, y, z;
        uv = uv * 2.0 - 1.0;

        switch (face)
        {
            case 0:
                z = 1.0f;
                x = uv.x;
                y = uv.y;
                break;
            case 1:
                z = -1.0f;
                x = -uv.x;
                y = uv.y;
                break;
            case 2:
                x = -1.0f;
                z = uv.x;
                y = uv.y;
                break;
            case 3:
                x = 1.0f;
                z = -uv.x;
                y = uv.y;
                break;
            case 4:
                y = 1.0f;
                x = uv.x;
                z = -uv.y;
                break;
            case 5:
                y = -1.0f;
                x = uv.x;
                z = uv.y;
                break;
        };

        return Vector3f(x, y, z).normalized();
    }
};

#endif