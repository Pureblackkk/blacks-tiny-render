#include<iostream>
#include<tgaimage.h>
#include<pngimage.h>
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
#include<cubemap.h>

using namespace std;

int main(int argc, char** argv) {
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    // Initit scene, camera, renderer
    Scene scene;
    // OrthoCamera camera(-1.05, 1.05, -1.05, 1.05, 0.01, 1000);
    PerspectiveCamera camera(60, 1.0, 0.01, 1000);
    Renderer renderer(screenWidth, screenHeight);

    // Set camera position, up, look at
    camera.position(0.0, 0.0, 3.0);
    camera.lookat(0.0, 0.0, 0.0);
    camera.up(0.0, 1.0, 0.0);

    // Add oribit control
    OribitControl orbitControl(camera);

    // Load geometry
    Geometry geo;
    std::string path = "../obj/pbr_sphere/cube.obj";
    Loader::loadGeometry(geo, path, true);

    // Define material
    Material objMaterial(PBR_DIRECT_SHADER);
    std::map<std::string, std::string> texturePathMap;
    // texturePathMap["default"] = "../obj/skybox/front.tga";
    texturePathMap["default"] = "../obj/pbr_sphere/space-cruiser-panels2_albedo.tga";
    texturePathMap["albedo"] = "../obj/pbr_sphere/space-cruiser-panels2_albedo.tga";
    texturePathMap["norm"] = "../obj/pbr_sphere/space-cruiser-panels2_normal-ogl.tga";
    texturePathMap["metallic"] = "../obj/pbr_sphere/space-cruiser-panels2_metallic.tga";
    texturePathMap["roughness"] = "../obj/pbr_sphere/space-cruiser-panels2_roughness.tga";
    texturePathMap["ao"] = "../obj/pbr_sphere/space-cruiser-panels2_ao.tga";
    objMaterial.bindTexturesByPathMap(texturePathMap);

    // Combine geometry and material to generate mesh
    Mesh mesh(geo, objMaterial);

    // Init light
    Light light;
    light.position(10.0, 10.0, 10.0);
    // Radiance
    light.color(15.0, 15.0, 15.0);

    // Init skybox
    Cubemap cubemap(
        "../obj/skybox/front.tga",
        "../obj/skybox/back.tga",
        "../obj/skybox/left.tga",
        "../obj/skybox/right.tga",
        "../obj/skybox/up.tga",
        "../obj/skybox/down.tga"
    );
    Material skyBoxMaterial(SKYBOX_SHADER);
    skyBoxMaterial.bindCubemap(cubemap);
    Mesh skybox(geo, skyBoxMaterial); // Re-use the cube geometry here
    skybox.scale(30.0f, 30.0f, 30.0f);


    // Add object to scene
    scene.add(mesh);

    // Add light to scene
    scene.add(light);

    // Add sky box to scene
    scene.add(skybox);

    // Animation start
    SD2GUI::init(screenWidth, screenHeight, &orbitControl);
    while(SD2GUI::loop()) {
        renderer.render(scene, camera);
        SD2GUI::update();
    }
    SD2GUI::quit();

	return 0;
}