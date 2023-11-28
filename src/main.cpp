#include<iostream>
#include<tgaimage.h>
#include<matrix4.h>
#include<geometry.h>
#include<loader.h>
#include<renderer.h>
#include<shader.h>
#include<scene.h>
#include<camera.h>
#include<mesh.h>

using namespace std;
using std::cout;

int main(int argc, char** argv) {
    // Initit scene, camera, renderer
    Scene scene;
    OrthoCamera camera(-1.2, 1.2, -1.2, 1.2, 0.01, 100);
    Renderer renderer(500, 500);

    // Set camera position, up, look at
    camera.position(Vector3f(0.0, 0.0, 1.0));
    camera.lookat(Vector3f(0.0, 0.0, 0.0));
    camera.up(Vector3f(0.0, 1.0, 0.0));
    
    // Load geometry 1
    Geometry geo;
    // std::string path = "../obj/floor/floor.obj";
    std::string path = "../obj/head/head.obj";
    Loader::loadGeometry(geo, path);

    // Define material
    Material material(TEXTURE_SHADER);
    TGAImage defaultTexture;
    // defaultTexture.read_tga_file("../obj/floor/floor.tga");
    // TODO: fix the texture bug
    defaultTexture.read_tga_file("../obj/head/head.tga");
    defaultTexture.flip_vertically();
    material.bindDefaultTexture(&defaultTexture);

    // Combine geometry and material to generate mesh
    Mesh mesh(geo, material);

    // Add mesh to scene
    scene.add(mesh);

    // Define output path
    renderer.render(scene, camera, "framebuffer.tga");

	return 0;
}