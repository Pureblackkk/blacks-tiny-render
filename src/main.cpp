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
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    // Initit scene, camera, renderer
    Scene scene;
    // OrthoCamera camera(-1.2, 1.2, -1.2, 1.2, 0.01, 100);
    PerspectiveCamera camera(60, 1.0, 0.01, 100);
    Renderer renderer(screenWidth, screenHeight);

    // Set camera position, up, look at
    camera.position(Vector3f(0.0, 1.0, 3.0));
    camera.lookat(Vector3f(0.0, 0.0, 0.0));
    camera.up(Vector3f(0.0, 1.0, 0.0));
    
    // Load geometry 1
    Geometry geo;
    // std::string path = "../obj/floor/floor.obj";
    std::string path = "../obj/diablo3_pose/diablo3_pose.obj";
    Loader::loadGeometry(geo, path);

    // Define material
    Material material(TEXTURE_SHADER);
    TGAImage defaultTexture;
    // defaultTexture.read_tga_file("../obj/floor/floor.tga");
    Loader::loadTexture(defaultTexture, "../obj/diablo3_pose/diablo3_pose_diffuse.tga");
    material.bindDefaultTexture(&defaultTexture);

    // Combine geometry and material to generate mesh
    Mesh mesh(geo, material);

    // Add mesh to scene
    scene.add(mesh);

    // Animation start
    SD2GUI::init(screenWidth, screenHeight);
    while(!SD2GUI::isQuit()) {
        renderer.render(scene, camera);
        SD2GUI::update();
    }
    SD2GUI::quit();

	return 0;
}