#pragma once

#include <string>
#include "core/Vector2.h"
#include "nlohmann/json_fwd.hpp"
#include <memory>

class Player;

class Level {
public:
    Level(const std::string& filePath);
    ~Level();

    const Vector2& getPlayerStartPosition() const;
    Player* getPlayer() const;

private:
    void loadFromFile(const std::string& filePath);

    Vector2 m_playerStartPosition;
    std::unique_ptr<Player> m_pPlayer;
    // We'll add tile data and entities here later
}; 