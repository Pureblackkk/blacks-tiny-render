#ifndef DISPLAYER_H
#define DISPLAYER_H

#include<string>
#include<buffer.h>
#include<vector4.h>
#include<tgaimage.h>
#include<sdl2.h>

class Displayer {
    public:
        void static offlineDraw(std::string path, Buffer<Uint32> *frameBuffer) {
            int width = frameBuffer->width();
            int height = frameBuffer->height();

            TGAImage image(width, height, TGAImage::RGB);

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    Uint32 frameColor = frameBuffer->get(i, j);
                    Vector4i frameColorRGBA =  SD2GUI::getRGBA(frameColor);
                    if (
                        frameColorRGBA.x == 0 
                        && frameColorRGBA.y == 0 
                        && frameColorRGBA.z == 0 
                        && frameColorRGBA.w == 0
                    ) continue;

                    Color color = Color(
                        frameColorRGBA.x,
                        frameColorRGBA.y,
                        frameColorRGBA.z,
                        frameColorRGBA.w
                    );

                    image.set(i, j, color);
                }
            }
            
            // Output to path
            image.write_file(path.c_str());
        }

        void static realTimeDraw(Buffer<Uint32> *frameBuffer) {
            int width = frameBuffer->width();
            int height = frameBuffer->height();

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    // if (r == 0 && g == 0 && b == 0 && alpha == 0) continue;
                    Uint32 pixelColor = frameBuffer->get(i, j);
                    SD2GUI::setPixel(i, j, pixelColor);
                }
            }
        }

        void static realTimeDrawMem(Buffer<Uint32> *frameBuffer) {
            SD2GUI::setBuffer(frameBuffer);
        }
};

#endif