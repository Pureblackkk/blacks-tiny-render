#ifndef SD2GUI_H
#define SD2GUI_H

#include<iostream>
#include<camera.h>
#include<SDL2/SDL.h>

class SD2GUI {
    public:
        bool init(const int width, const int height);
        void setPixel(const int x, const int y, const Vector4i &color);
        void update();
        void start();
        void quit();

    private:
        int pWidth;
        int pHeight;
        SDL_Window *window;
};

#endif