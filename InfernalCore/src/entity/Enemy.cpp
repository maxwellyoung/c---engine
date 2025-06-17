#include "entity/Enemy.h"
#include "gfx/TextureManager.h"
#include "game/Level.h"
#include <SDL2/SDL.h>

Enemy::Enemy(Level* pLevel) : m_pLevel(pLevel), m_direction(1), m_speed(100.0f), m_pTexture(nullptr) {
    m_pTexture = TextureManager::getInstance().load("assets/sprites/enemy.png");
}

Enemy::~Enemy() {
    // Enemy-specific cleanup
}

void Enemy::update(double deltaTime) {
    float newX = m_position.x + m_direction * m_speed * deltaTime;
    
    SDL_Rect enemyRect = { (int)newX, (int)m_position.y, 32, 32 };
    if (m_pLevel->isColliding(enemyRect)) {
        m_direction *= -1; // Reverse direction
    } else {
        m_position.x = newX;
    }
}

void Enemy::render(SDL_Renderer* renderer) {
    if (!m_pTexture) return;

    SDL_Rect destRect = {
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        32, // width
        32  // height
    };

    SDL_RenderCopy(renderer, m_pTexture, nullptr, &destRect);
} 