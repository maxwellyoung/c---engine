#pragma once

#include "entity/Entity.h"

// Forward declarations
struct SDL_Texture;
class Level;

class Enemy : public Entity {
public:
    Enemy(Level* pLevel);
    ~Enemy();

    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) override;

private:
    SDL_Texture* m_pTexture;
    Level* m_pLevel;
    int m_direction;
    float m_speed;
}; 