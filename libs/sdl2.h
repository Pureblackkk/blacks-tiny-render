#ifndef SD2GUI_H
#define SD2GUI_H

#include<iostream>
#include<camera.h>
#include<buffer.h>
#include<SDL2/SDL.h>
#include<orbitControl.h>


class SD2GUI {
    public:
        static bool init(const int width, const int height, OribitControl *orbitControl = nullptr);
        static void setPixel(int x, int y, Uint32 &pixelColor);
        static void setPixel(const int x, const int y, const Vector4i &color);
        static void setBuffer(Buffer<Uint32> *buffer);
        static Uint32 mapRGBA(Vector4f &color);
        static Vector4i getRGBA(Uint32 &color);
        static void update();
        static bool loop();
        static void quit();
        static void clean();
        static SDL_PixelFormat* pixelFormat();

    private:
        static int pWidth;
        static int pHeight;
        static OribitControl *pOrbitControl;
        static SDL_PixelFormat *pPixelFormat;
        static SDL_Window *window;
        static SDL_Surface *surface;
        static void mouseDown(const Vector2f position);
        static void mouseUp();
        static void mouseMove(const Vector2f position, const Vector2i &size);
        static void mouseScroll(const float scroll);
};

#endif