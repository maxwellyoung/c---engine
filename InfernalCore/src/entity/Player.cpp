#include "entity/Player.h"
#include "input/Input.h"
#include <SDL2/SDL.h>

Player::Player() : m_speed(200.0f) {
    // Player-specific initialization can go here
}

Player::~Player() {
    // Player-specific cleanup
}

void Player::update(double deltaTime) {
    Input& input = Input::getInstance();
    
    Vector2 velocity = {0.0f, 0.0f};

    if (input.isKeyHeld(SDL_SCANCODE_W)) {
        velocity.y = -1.0f;
    }
    if (input.isKeyHeld(SDL_SCANCODE_S)) {
        velocity.y = 1.0f;
    }
    if (input.isKeyHeld(SDL_SCANCODE_A)) {
        velocity.x = -1.0f;
    }
    if (input.isKeyHeld(SDL_SCANCODE_D)) {
        velocity.x = 1.0f;
    }

    // Normalize diagonal movement
    if (velocity.x != 0.0f && velocity.y != 0.0f) {
        velocity.x *= 0.7071f; // approximation of 1/sqrt(2)
        velocity.y *= 0.7071f;
    }

    m_position.x += velocity.x * m_speed * deltaTime;
    m_position.y += velocity.y * m_speed * deltaTime;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect playerRect = {
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        32, // width
        32  // height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(renderer, &playerRect);
} 