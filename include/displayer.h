#ifndef DISPLAYER_H
#define DISPLAYER_H

#include<string>
#include<buffer.h>
#include<vector4.h>
#include<tgaimage.h>
#include<sdl2.h>

class Displayer {
    public:
        void static offlineDraw(std::string path, Buffer<Vector4f> *frameBuffer) {
            int width = frameBuffer->width();
            int height = frameBuffer->height();

            TGAImage image(width, height, TGAImage::RGB);

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    Vector4f frameColor = frameBuffer->get(i, j);
                    frameColor *= 255.0f;
                    int r = static_cast<int>(frameColor.x);
                    int g = static_cast<int>(frameColor.y);
                    int b = static_cast<int>(frameColor.z);
                    int alpha = static_cast<int>(frameColor.w);
                    if (r == 0 && g == 0 && b == 0 && alpha == 0) continue;
                    TGAColor color = TGAColor(r, g, b, alpha);
                    image.set(i, j, color);
                }
            }

            // Make origin from left bottom corner
            image.flip_vertically();

            // Output to path
            image.write_tga_file(path.c_str());
        }

        void static realTimeDraw(Buffer<Vector4f> *frameBuffer) {
            int width = frameBuffer->width();
            int height = frameBuffer->height();
            
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    Vector4f frameColor = frameBuffer->get(i, j);
                    frameColor *= 255.0f;
                    int r = static_cast<int>(frameColor.x);
                    int g = static_cast<int>(frameColor.y);
                    int b = static_cast<int>(frameColor.z);
                    int alpha = static_cast<int>(frameColor.w);
                    // if (r == 0 && g == 0 && b == 0 && alpha == 0) continue;
                    SD2GUI::setPixel(i, j, Vector4i(r, g, b, alpha));
                }
            }
        }
};

#endif