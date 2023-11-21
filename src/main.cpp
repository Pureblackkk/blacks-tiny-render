#include <tgaimage.h>
#include <vector3.h>
#include <vector4.h>
#include <matrix4.h>
#include <iostream>

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
    Matrix4f v = Matrix4f(
        Vector4f(1., 1., 1., 1.),
        Vector4f(2., 2., 2., 2.),
        Vector4f(0., 0., 2., 0.),
        Vector4f(0., 0., 0., 2.)
    );

    TransformParameters testParameters;
    Vector3f test = Vector3f(Vector2f(1., 2.), 0.);
    test.print();
	return 0;
}