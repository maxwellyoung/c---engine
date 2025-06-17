#pragma once

#include <SDL2/SDL_scancode.h>
#include <unordered_map>

class Input {
public:
    static Input& getInstance();

    void onKeyDown(SDL_Scancode scancode);
    void onKeyUp(SDL_Scancode scancode);

    bool isKeyHeld(SDL_Scancode scancode) const;

    // Delete copy and move constructors and assign operators
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
    Input(Input&&) = delete;
    void operator=(Input&&) = delete;

private:
    Input() = default;
    std::unordered_map<SDL_Scancode, bool> m_heldKeys;
}; 