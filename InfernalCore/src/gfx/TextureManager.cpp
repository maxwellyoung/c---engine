#include "gfx/TextureManager.h"
#include "core/Log.h"
#include <SDL2/SDL_image.h>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::init(SDL_Renderer* renderer) {
    m_pRenderer = renderer;
    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Log::error("IMG_Init Error: " + std::string(IMG_GetError()));
    }
}

SDL_Texture* TextureManager::load(const std::string& filePath) {
    // Check if texture is already loaded
    if (m_textureMap.count(filePath)) {
        return m_textureMap[filePath];
    }

    SDL_Texture* texture = IMG_LoadTexture(m_pRenderer, filePath.c_str());
    if (texture == nullptr) {
        Log::error("Failed to load texture: " + filePath + " - " + std::string(IMG_GetError()));
        return nullptr;
    }

    Log::info("Successfully loaded texture: " + filePath);
    m_textureMap[filePath] = texture;
    return texture;
}

TextureManager::~TextureManager() {
    for (auto const& [key, val] : m_textureMap) {
        SDL_DestroyTexture(val);
    }
    m_textureMap.clear();
    IMG_Quit();
} 