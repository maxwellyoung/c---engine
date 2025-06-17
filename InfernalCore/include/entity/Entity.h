#pragma once

#include "core/Vector2.h"

// Forward declaration
struct SDL_Renderer;

class Entity {
public:
    Entity() : m_position({0.0f, 0.0f}) {}
    virtual ~Entity() = default;

    virtual void update(double deltaTime) {}
    virtual void render(SDL_Renderer* renderer) {}

    const Vector2& getPosition() const { return m_position; }
    void setPosition(const Vector2& position) { m_position = position; }

protected:
    Vector2 m_position;
}; 