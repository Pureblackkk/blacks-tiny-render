#include<sdl2.h>

int SD2GUI::pWidth = 0;
int SD2GUI::pHeight = 0;
SDL_Window* SD2GUI::window = nullptr;

bool SD2GUI::init(const int width, const int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "SDL could not initialized with error: " <<  SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "sdl2gui",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width, height,
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (window == NULL) {
        std::cout << "SDL could not create window with error: " <<  SDL_GetError() << std::endl;
        return 1;
    }

    pWidth = width;
    pHeight = height;

    return 0;
}

void SD2GUI::setPixel(int x, int y, const Vector4i &color) {
    // Transform x, y since the original of SDL GUI is on the top-left 
    // while that of out screen space is located on the bottom-left
    y = pHeight - 1 - y;

    // Get window surface
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    Uint32* pixels = static_cast<Uint32*>(surface->pixels);

    // Set color
    Uint32 pixelColor = SDL_MapRGBA(surface->format, color.x, color.y, color.z, color.w);
    // TOOD: figure out why
    pixels[y * pWidth * 4 + x * 2] = pixelColor;
}

void SD2GUI::update() {
    SDL_UpdateWindowSurface(window);
}

bool SD2GUI::isQuit() {
    SDL_Event windowEvent;
    if (SDL_PollEvent(&windowEvent)) {
        if (SDL_QUIT == windowEvent.type) {
            std::cout << "SDL2GUI quit" << std::endl;
            return true;
        }
    }
    return false;
}

void SD2GUI::quit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}