#include "entity/Player.h"
#include "input/Input.h"
#include "gfx/TextureManager.h"
#include "game/Level.h"
#include <SDL2/SDL.h>

Player::Player(Level* pLevel) : m_pLevel(pLevel), m_speed(200.0f), m_pTexture(nullptr) {
    m_pTexture = TextureManager::getInstance().load("assets/sprites/player.png");
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

    float newX = m_position.x + velocity.x * m_speed * deltaTime;
    float newY = m_position.y + velocity.y * m_speed * deltaTime;

    SDL_Rect playerRect = { (int)newX, (int)m_position.y, 32, 32 };
    if (!m_pLevel->isColliding(playerRect)) {
        m_position.x = newX;
    }

    playerRect = { (int)m_position.x, (int)newY, 32, 32 };
    if (!m_pLevel->isColliding(playerRect)) {
        m_position.y = newY;
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (!m_pTexture) return; // Don't render if texture failed to load

    SDL_Rect destRect = {
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        32, // width
        32  // height
    };

    SDL_RenderCopy(renderer, m_pTexture, nullptr, &destRect);
} 