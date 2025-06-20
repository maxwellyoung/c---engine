#pragma once

#include "entity/Entity.h"

// Forward declarations
struct SDL_Texture;
class Level;

class Player : public Entity {
public:
    Player(Level* pLevel);
    ~Player();

    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) override;

private:
    float m_speed;
    SDL_Texture* m_pTexture;
    Level* m_pLevel;
}; 