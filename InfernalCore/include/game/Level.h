#pragma once

#include <string>
#include <vector>
#include "core/Vector2.h"
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <SDL2/SDL.h>

class Player;
class Enemy;

class Level {
public:
    Level(const std::string& filePath);
    ~Level();

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);
    const Vector2& getPlayerStartPosition() const;
    Player* getPlayer() const;
    bool isColliding(const SDL_Rect& rect) const;

private:
    void loadFromFile(const std::string& filePath);

    Vector2 m_playerStartPosition;
    std::unique_ptr<Player> m_pPlayer;
    SDL_Texture* m_pTilesetTexture;
    std::vector<std::vector<int>> m_tiles;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    // We'll add tile data and entities here later
}; 