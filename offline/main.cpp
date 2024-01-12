#include <shader.h>
#include <cubemap.h>
#include <loader.h>
#include <imageBasedLighting.h>

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::runtime_error("No args recieved. Please input skycube directory");
    }

    std::string cubeDirPath = argv[1];
    std::string outputDirPath = argv[2];

    ImageBasedLighting ibl(cubeDirPath, outputDirPath);
    ibl.generateIntegralImage();

    return 0;
}