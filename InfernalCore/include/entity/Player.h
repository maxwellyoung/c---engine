#pragma once

#include "entity/Entity.h"

class Player : public Entity {
public:
    Player();
    ~Player();

    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) override;

private:
    float m_speed;
}; 