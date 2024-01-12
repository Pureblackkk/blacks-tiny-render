#ifndef OFFIBL_H
#define OFFIBL_H

#include <string>
#include <cubemap.h>

class ImageBasedLighting {
    public:
        ImageBasedLighting(const std::string &cubemapDirPath, const std::string &outputDirPath): cubemapPath(cubemapDirPath), outputPath(outputDirPath) {};
        void generateIntegralImage(unsigned int type = 0);

    private: 
        std::string cubemapPath;
        std::string outputPath;
        Cubemap *cubemap = nullptr;
        void readCubemap();
        void riemannIntegral(Image *cubeImages[6]);
        void monteCarloIntegral(Image *cubeImages[6]);
        void sphHarmonicsIntegral(Image *cubeImages[6]);
        void outputImage(Image *cubeImages[6]);
};

void ImageBasedLighting::generateIntegralImage(unsigned int type) {
    // Type 0: Riemann integral
    // Type 1: Monte Carlo integral
    // Type 2: Spherical Harmonics integral

    // Read cubemap 
    readCubemap();

    // Set cube image list for output
    Image *cubeImages[6];

    switch (type) {
        case 0:
            riemannIntegral(cubeImages);
            break;
        case 1:
            monteCarloIntegral(cubeImages);
            break;
        case 2:
            sphHarmonicsIntegral(cubeImages);
            break;
        default:
            std::runtime_error("Type error");
    };


    // Write cube image
    outputImage(cubeImages);
}

void ImageBasedLighting::readCubemap() {
    std::string front = cubemapPath + "/front.tga";
    std::string back = cubemapPath + "/back.tga";
    std::string left = cubemapPath + "/left.tga";
    std::string right = cubemapPath + "/right.tga";
    std::string up = cubemapPath + "/up.tga";
    std::string down = cubemapPath + "/down.tga";

    cubemap = new Cubemap(
        front,
        back,
        left,
        right,
        up,
        down
    );    
}

void ImageBasedLighting::riemannIntegral(Image *cubeImages[6]) {
    // Generate image for 6 faces
    for (int face = 0; face < 6; face++) {
        Image *currentFace = cubemap->getFaces(face);
        int imageWidth = currentFace->get_width();
        int imageHeight = currentFace->get_height();

        Image *imageToWrite = new TGAImage(imageWidth, imageHeight, TGAImage::RGB);

        #pragma omp parallel for num_threads(20)
        for (int i = 0; i < imageWidth; i++) {
            for (int j = 0; j < imageHeight; j++) {
                // Get uv coordinate
                Vector2f uv(float(i) / (imageWidth - 1), float(j) / (imageHeight - 1));

                // Get direction vector from uv coordinate
                Vector3f normal = Cubemap::uvToDir(face, uv);

                // Create tagent space
                Vector3f tangent(0, 1, 0);
                float normalYDot = tangent.dot(normal);

                if (std::abs(normalYDot - 1.0) < 1e-6) {
                    tangent = Vector3f(1, 0, 0);
                } else if (std::abs(normalYDot + 1.0) < 1e-6) {
                    tangent = Vector3f(-1, 0, 0);
                } else {
                    tangent = Vector3f(0, 1, 0).cross(normal).normalized();
                }

                Vector3f bitangent = normal.cross(tangent).normalized();

                // Integral sum
                float sampleDeltaAngle = 0.025;
                int N1 = 0;
                int N2 = 0;
                Vector3f sum;

                for (float phi = 0; phi < (2.0 * M_PI); phi += sampleDeltaAngle) {
                    N2 = 0;
                    for (float theta = 0; theta < M_PI; theta += sampleDeltaAngle) {
                        float cosTheta = std::cos(theta);
                        float sinTheta = std::sin(theta);
                        float x = sinTheta * std::cos(phi);
                        float y = sinTheta * std::sin(phi);
                        float z = cosTheta;

                        Vector3f worldDir = tangent * x + bitangent * y + normal * z;
                        Vector3f color = Shader::sampleCubeRGBA(cubemap, worldDir).vectorThree();
                        sum += color * cosTheta * sinTheta;

                        N2++;
                    }
                    N1++;
                }
                
                sum = sum * (M_PI * M_PI / (N1 * N2));

                // Write to the face on the current uv coordinate
                Color toSetColor(
                    static_cast<int>(sum.x * 255.0),
                    static_cast<int>(sum.y * 255.0),
                    static_cast<int>(sum.z * 255.0),
                    255
                );
                imageToWrite->set(i, imageWidth - j - 1, toSetColor);
            }
        }

        // Set image to list
        cubeImages[face] = imageToWrite;
        std::cout << "Face " << face << " generated" << std::endl;
    }
}

void ImageBasedLighting::monteCarloIntegral(Image *cubeImages[6]){}
void ImageBasedLighting::sphHarmonicsIntegral(Image *cubeImages[6]){}

void ImageBasedLighting::outputImage(Image *cubeImages[6]) {
    std::string nameList[6]{"front", "back", "left", "right", "up", "down"};

    for (int idx = 0; idx < 6; idx++) {
        std::string outputname = outputPath + "/" + nameList[idx] + ".tga";

        cubeImages[idx]->write_file(outputname.c_str());
    }
}

#endif