#pragma once

#include <cstdint>
#include <memory>
#include "game/Level.h"

// Forward declarations
struct SDL_Window;
struct SDL_Renderer;
class Player;

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
    
    std::unique_ptr<Level> m_pCurrentLevel;
    Player* m_pPlayer;
}; 