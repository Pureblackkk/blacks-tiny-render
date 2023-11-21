#include <iostream>
#include <tgaimage.h>
#include <vector3.h>
#include <vector4.h>
#include <matrix4.h>
#include <geometry.h>
#include <loader.h>

using namespace std;
using std::cout;


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
    image.set(0, 0, red);
    image.set(40, 40, red);
    image.set(60, 60, red);
    image.set(80, 80, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

    // Test
    Geometry geo;
    std::string a = "../obj/floor/floor.obj";
    Loader::loadGeometry(geo, a);
    geo.print();

	return 0;
}