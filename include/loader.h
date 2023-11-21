#ifndef LOADER_H
#define LOADER_H

#include<iostream>
#include<sstream>
#include<vector2.h>
#include<vector3.h>
#include<geometry.h>
#include<fstream>

class Loader {
    public:
        static int loadGeometry(Geometry &geo, const std::string filename);
};

#endif