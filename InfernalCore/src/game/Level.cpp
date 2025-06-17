#include "game/Level.h"
#include "core/Log.h"
#include "entity/Player.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

Level::Level(const std::string& filePath) {
    loadFromFile(filePath);
}

Level::~Level() {
    // Nothing to do here yet
}

void Level::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Log::error("Failed to open level file: " + filePath);
        return;
    }

    try {
        json data;
        file >> data;

        if (data.contains("player_start") && data["player_start"].is_object()) {
            m_playerStartPosition.x = data["player_start"].value("x", 0.0f);
            m_playerStartPosition.y = data["player_start"].value("y", 0.0f);
        } else {
            Log::warn("Level file does not contain player_start position.");
            m_playerStartPosition = {0.0f, 0.0f};
        }

        // Create the player and set its position
        m_pPlayer = std::make_unique<Player>();
        m_pPlayer->setPosition(m_playerStartPosition);

        Log::info("Successfully loaded level: " + filePath);

    } catch (const json::parse_error& e) {
        Log::error("Failed to parse level file: " + filePath + " - " + e.what());
    }
}

const Vector2& Level::getPlayerStartPosition() const {
    return m_playerStartPosition;
}

Player* Level::getPlayer() const {
    return m_pPlayer.get();
} 