#include "input/Input.h"

Input& Input::getInstance() {
    static Input instance;
    return instance;
}

void Input::onKeyDown(SDL_Scancode scancode) {
    m_heldKeys[scancode] = true;
}

void Input::onKeyUp(SDL_Scancode scancode) {
    m_heldKeys[scancode] = false;
}

bool Input::isKeyHeld(SDL_Scancode scancode) const {
    if (m_heldKeys.count(scancode)) {
        return m_heldKeys.at(scancode);
    }
    return false;
} 