#pragma once

#include <string>
#include <unordered_map>

// Forward declarations
struct SDL_Texture;
struct SDL_Renderer;

class TextureManager {
public:
    static TextureManager& getInstance();

    void init(SDL_Renderer* renderer);
    SDL_Texture* load(const std::string& filePath);

    // Delete copy/move constructors and assignment operators
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

private:
    TextureManager() = default;
    ~TextureManager();

    SDL_Renderer* m_pRenderer = nullptr;
    std::unordered_map<std::string, SDL_Texture*> m_textureMap;
}; 