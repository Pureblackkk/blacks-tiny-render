#include<sdl2.h>

int SD2GUI::pWidth = 0;
int SD2GUI::pHeight = 0;
OribitControl* SD2GUI::pOrbitControl = nullptr;
SDL_Window* SD2GUI::window = nullptr;

bool SD2GUI::init(const int width, const int height, OribitControl *orbitControl) {
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
    pOrbitControl = orbitControl;

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

void SD2GUI::clean() {
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, 0);
}

void SD2GUI::update() {
    SDL_UpdateWindowSurface(window);
}

bool SD2GUI::loop() {
    SDL_Event windowEvent;
    if (SDL_PollEvent(&windowEvent)) {
        switch (windowEvent.type) {
            // Quit event
            case SDL_QUIT:
                std::cout << "SDL2GUI quit" << std::endl;
                return false;
            // Mouse down event
            case SDL_MOUSEBUTTONDOWN:
                mouseDown(Vector2f(windowEvent.motion.x, pHeight - windowEvent.motion.y));
                // std::cout << "Mouse button pressed at (" << windowEvent.button.x << ", " << windowEvent.button.y << ")" << std::endl;
                break;
            // Mouse up event
            case SDL_MOUSEBUTTONUP:
                mouseUp();
                break;
            // Mouse move event
            case SDL_MOUSEMOTION:
                mouseMove(
                    Vector2f(windowEvent.motion.x, pHeight - windowEvent.motion.y - 1),
                    Vector2i(pWidth, pHeight)
                );
                // std::cout << "Mouse moved to (" << windowEvent.motion.x << ", " << windowEvent.motion.y << ")" << std::endl;
                break;
            // Scroll event
            case SDL_MOUSEWHEEL:
                mouseScroll(windowEvent.wheel.y);
                // std::cout << "Mouse scroll" <<  windowEvent.wheel.y << std::endl;
                break;
        }
    }
    return true;
}

void SD2GUI::quit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SD2GUI::mouseUp() {
    if (pOrbitControl == nullptr) return;
    pOrbitControl->lock(true);
}

void SD2GUI::mouseDown(const Vector2f position) {
    if (pOrbitControl == nullptr) return;
    pOrbitControl->lock(false);
    // Set previous position
    pOrbitControl->setPosition(position);
}

void SD2GUI::mouseMove(const Vector2f position, const Vector2i &size) {
    if (pOrbitControl == nullptr) return;
    if (pOrbitControl->lock()) return;
    pOrbitControl->rotate(position, size);
}

void SD2GUI::mouseScroll(float scroll) {
    if (pOrbitControl == nullptr) return;
    pOrbitControl->zoom(scroll);
}


