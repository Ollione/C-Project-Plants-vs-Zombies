
#include "../Headers/Textures.h"

TextureManager::~TextureManager() = default;

sf::Texture* TextureManager::getTexture(const std::string& filename) {
    if (textures.count(filename) == 0) {    // If the texture is not found in the map
        auto texture = std::make_unique<sf::Texture>(); // Create a new texture
        if (!texture->loadFromFile(filename)) { // If the texture fails to load
            return nullptr; // Return nullptr if the texture fails to load
        }
        textures[filename] = std::move(texture);    // Move the texture to the map
    }
    return textures[filename].get();    // Return the texture pointer
}