#include "core/Game.h"
#include "core/Log.h"
#include "game/Level.h"
#include "entity/Player.h"
#include "input/Input.h"
#include "gfx/TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>

// Forward declare to avoid including SDL in the header
struct SDL_Window;
struct SDL_Renderer;

Game::Game() : m_isRunning(false), m_pWindow(nullptr), m_pRenderer(nullptr), m_lastTime(0), m_accumulator(0.0) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Log::error("SDL_Init Error: " + std::string(SDL_GetError()));
        return;
    }

    m_pWindow = SDL_CreateWindow("Infernal Core", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr) {
        Log::error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_pRenderer == nullptr) {
        SDL_DestroyWindow(m_pWindow);
        Log::error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return;
    }

    // Initialize managers
    TextureManager::getInstance().init(m_pRenderer);

    m_isRunning = true;
    m_lastTime = SDL_GetPerformanceCounter();

    // Load the initial level
    m_pCurrentLevel = std::make_unique<Level>("assets/maps/level1.json");
    m_pPlayer = m_pCurrentLevel->getPlayer();

    Log::info("Infernal Core engine started successfully.");
}

Game::~Game() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void Game::run() {
    const double deltaTime = 1.0 / 60.0;

    while (m_isRunning) {
        uint64_t now = SDL_GetPerformanceCounter();
        double frameTime = (now - m_lastTime) / (double)SDL_GetPerformanceFrequency();
        m_lastTime = now;

        m_accumulator += frameTime;

        while (m_accumulator >= deltaTime) {
            processEvents();
            update();
            m_accumulator -= deltaTime;
        }

        render();
    }
}

void Game::processEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            m_isRunning = false;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.repeat == 0) {
                Input::getInstance().onKeyDown(e.key.keysym.scancode);
            }
        } else if (e.type == SDL_KEYUP) {
            Input::getInstance().onKeyUp(e.key.keysym.scancode);
        }
    }
}

void Game::update() {
    // Game logic will go here, running at a fixed rate
    if (m_pCurrentLevel) {
        m_pCurrentLevel->update(1.0/60.0);
    }
    if (m_pPlayer) {
        m_pPlayer->update(1.0/60.0); // Fixed delta time for now
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 25, 20, 20, 255);
    SDL_RenderClear(m_pRenderer);

    // Render the level
    if (m_pCurrentLevel) {
        m_pCurrentLevel->render(m_pRenderer);
    }

    // Render the player
    if (m_pPlayer) {
        m_pPlayer->render(m_pRenderer);
    }

    SDL_RenderPresent(m_pRenderer);
} 