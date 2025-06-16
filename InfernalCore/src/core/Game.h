#pragma once
#include <cstdint>

// Forward declarations to avoid including SDL headers in our main header
struct SDL_Window;
struct SDL_Renderer;

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update();
    void render();

    bool m_isRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    uint64_t m_lastTime;
    double m_accumulator;
}; 