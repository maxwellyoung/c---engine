#include "game/Level.h"
#include "core/Log.h"
#include "entity/Player.h"
#include "entity/Enemy.h"
#include "gfx/TextureManager.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

Level::Level(const std::string& filePath) : m_pTilesetTexture(nullptr) {
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

        if (data.contains("tileset")) {
            std::string tilesetPath = data["tileset"];
            m_pTilesetTexture = TextureManager::getInstance().load(tilesetPath);
        }

        if (data.contains("tiles") && data["tiles"].is_array()) {
            for (const auto& row : data["tiles"]) {
                m_tiles.push_back(row.get<std::vector<int>>());
            }
        }

        // Create the player and set its position
        m_pPlayer = std::make_unique<Player>(this);
        m_pPlayer->setPosition(m_playerStartPosition);

        if (data.contains("enemies") && data["enemies"].is_array()) {
            for (const auto& enemyData : data["enemies"]) {
                auto enemy = std::make_unique<Enemy>(this);
                enemy->setPosition({enemyData.value("x", 0.0f), enemyData.value("y", 0.0f)});
                m_enemies.push_back(std::move(enemy));
            }
        }

        Log::info("Successfully loaded level: " + filePath);

    } catch (const json::parse_error& e) {
        Log::error("Failed to parse level file: " + filePath + " - " + e.what());
    }
}

void Level::render(SDL_Renderer* renderer) {
    if (!m_pTilesetTexture) {
        return;
    }

    int tileWidth = 32;
    int tileHeight = 32;

    for (size_t y = 0; y < m_tiles.size(); ++y) {
        for (size_t x = 0; x < m_tiles[y].size(); ++x) {
            int tileId = m_tiles[y][x];
            if (tileId != 0 && tileId != 1) { // Render only floor and wall tiles for now
                continue;
            }

            SDL_Rect srcRect = { tileId * tileWidth, 0, tileWidth, tileHeight };
            SDL_Rect destRect = { (int)x * tileWidth, (int)y * tileHeight, tileWidth, tileHeight };

            SDL_RenderCopy(renderer, m_pTilesetTexture, &srcRect, &destRect);
        }
    }

    for (const auto& enemy : m_enemies) {
        enemy->render(renderer);
    }
}

void Level::update(double deltaTime) {
    for (const auto& enemy : m_enemies) {
        enemy->update(deltaTime);
    }
}

bool Level::isColliding(const SDL_Rect& rect) const {
    int tileWidth = 32;
    int tileHeight = 32;

    int left_tile = rect.x / tileWidth;
    int right_tile = (rect.x + rect.w) / tileWidth;
    int top_tile = rect.y / tileHeight;
    int bottom_tile = (rect.y + rect.h) / tileHeight;

    for (int y = top_tile; y <= bottom_tile; ++y) {
        for (int x = left_tile; x <= right_tile; ++x) {
            if (x >= 0 && x < m_tiles[0].size() && y >= 0 && y < m_tiles.size()) {
                if (m_tiles[y][x] == 1) { // 1 is a wall tile
                    return true;
                }
            } else {
                // If the player is outside the map, it's a collision
                return true;
            }
        }
    }

    return false;
}

const Vector2& Level::getPlayerStartPosition() const {
    return m_playerStartPosition;
}

Player* Level::getPlayer() const {
    return m_pPlayer.get();
} 