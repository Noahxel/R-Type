#include "TextureLoader.hpp"

/**
 * @brief Get the index of a texture by its name from the texture list.
 *
 * @param textureName The name of the texture to find.
 * @return int The index of the texture in the list or -1 if not found.
 */
int TextureLoader::getTextureIndexByName(std::string textureName) {
    for (size_t i = 0, size = textureList.size(); i < size; i++) {
        if (textureList[i].first == textureName) {
            if (i > static_cast<size_t>(std::numeric_limits<int>::max())) {
                // Handle the error: log, throw exception, or use a special return value
                return -1; // or another appropriate value
            }
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * @brief Get the SFML Texture object by its name.
 *
 * @param textureName The name of the texture to retrieve.
 * @return sf::Texture* Pointer to the SFML Texture object or nullptr if not found.
 */
sf::Texture* TextureLoader::getTextureByName(const std::string& textureName) {
    int index = getTextureIndexByName(textureName);

    if (index > -1)
        return &textureList[index].second;
    return nullptr;
}

/**
 * @brief Check if the texture with the specified name is reverted.
 *
 * @param textureName The name of the texture to check.
 * @return true If the texture is reverted.
 * @return false Otherwise.
 */
bool TextureLoader::getRevertedByName(const std::string& textureName) {
    int index = getTextureIndexByName(textureName);

    if (index > -1)
        return isRevertList[index];
    return false;
}

/**
 * @brief Add a new texture to the texture list from a file path.
 *
 * @param texturePath The file path of the texture to load.
 * @param textureName The name to assign to the loaded texture.
 */
void TextureLoader::addTexture(const std::string& texturePath, std::string textureName) {
    if (!getTextureByName(textureName)) {
        sf::Texture newTexture;

        if (newTexture.loadFromFile(texturePath)) {
            std::pair<std::string, sf::Texture> newPair = std::make_pair(textureName, newTexture);
            textureList.push_back(newPair);
            isRevertList.push_back(isTextureReverted(texturePath));
            std::cout << "Texture added successfully: " << texturePath << std::endl;
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
    }
}

/**
 * @brief Determine if the texture is reverted based on the texture path.
 *
 * @param texturePath The file path of the texture.
 * @return true If the texture path contains '_reverted'.
 * @return false Otherwise.
 */
bool TextureLoader::isTextureReverted(std::string texturePath) {
    size_t foundPos = texturePath.find("_reverted");

    if (foundPos != std::string::npos) {
        return (true);
    } else {
        return (false);
    }
}
