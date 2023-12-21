#ifndef LOADER_H
#define LOADER_H

#include<iostream>
#include<sstream>
#include<vector2.h>
#include<vector3.h>
#include<geometry.h>
#include<tgaimage.h>
#include<fstream>

class Loader {
    public:
        static bool loadGeometry(Geometry &geo, const std::string filename);
        static bool loadTexture(Image &img, const char *filename);
};

#endif