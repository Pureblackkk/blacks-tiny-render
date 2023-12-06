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
#include<light.h>
#include<orbitControl.h>

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
    camera.position(0.0, 1.0, 3.0);
    camera.lookat(0.0, 0.0, 0.0);
    camera.up(0.0, 1.0, 0.0);

    // Add oribit control
    OribitControl orbitControl(camera);

    // Load geometry 1
    Geometry geo;
    // std::string path = "../obj/floor/floor.obj";
    std::string path = "../obj/diablo3_pose/diablo3_pose.obj";
    Loader::loadGeometry(geo, path);

    // Define material
    Material material(BLINNPHONE_SHADER);
    TGAImage defaultTexture;
    // defaultTexture.read_tga_file("../obj/floor/floor.tga");
    Loader::loadTexture(defaultTexture, "../obj/diablo3_pose/diablo3_pose_diffuse.tga");
    material.bindDefaultTexture(&defaultTexture);

    // Combine geometry and material to generate mesh
    Mesh mesh(geo, material);

    // Set mesh rotate and scale
    mesh.position(-0.5, 0.0, 0.0);
    mesh.rotate(0.1, 0.0, 0.0);
    mesh.scale(0.5, 0.5, 0.5);


    // Init light
    Light light;
    light.position(10.0, 10.0, 10.0);
    light.color(0.0, 1.0, 0.0);

    // Add mesh to scene
    scene.add(mesh);

    // Add light to scene
    scene.add(light);

    // Animation start
    SD2GUI::init(screenWidth, screenHeight, &orbitControl);
    while(SD2GUI::loop()) {
        renderer.render(scene, camera);
        SD2GUI::update();
    }
    SD2GUI::quit();

	return 0;
}