#ifndef SD2GUI_H
#define SD2GUI_H

#include<iostream>
#include<camera.h>
#include<SDL2/SDL.h>

class SD2GUI {
    public:
        static bool init(const int width, const int height);
        static void setPixel(const int x, const int y, const Vector4i &color);
        static void update();
        static bool isQuit();
        static void quit();    

    private:
        static int pWidth;
        static int pHeight;
        static SDL_Window *window;
};

#endif