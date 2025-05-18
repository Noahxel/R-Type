#pragma once

#include "../../../Graphic/GraphicComponents.hpp"

/**
 * @class TextureLoader
 * @brief Manages and loads textures for use in the game.
 *
 * This class is responsible for loading and storing textures from files,
 * and provides functionality to retrieve textures by their names.
 */
class TextureLoader {
   public:
    /**
     * @brief Constructs a new Texture Loader object.
     */
    TextureLoader() : textureList({}){};

    /**
     * @brief Add a new texture to the texture list from a given file path.
     * 
     * @param texturePath Path to the texture file.
     * @param textureName Name to assign to the loaded texture.
     */
    void addTexture(const std::string& texturePath, std::string textureName);

    /**
     * @brief Get the index of a texture in the list by its name.
     * 
     * @param textureName Name of the texture to find.
     * @return int The index of the texture in the list or -1 if not found.
     */
    int getTextureIndexByName(std::string textureName);

    /**
     * @brief Check if a texture is marked as reverted based on its file path.
     * 
     * @param texturePath Path to the texture file.
     * @return true If the texture is marked as reverted.
     * @return false Otherwise.
     */
    bool isTextureReverted(std::string texturePath);

    /**
     * @brief Get whether a texture is reverted by its name.
     * 
     * @param textureName Name of the texture.
     * @return true If the texture is reverted.
     * @return false Otherwise.
     */
    bool getRevertedByName(const std::string& textureName);

    /**
     * @brief Get the SFML Texture object by its name.
     * 
     * @param textureName Name of the texture to retrieve.
     * @return sf::Texture* Pointer to the SFML Texture object or nullptr if not found.
     */
    sf::Texture* getTextureByName(const std::string& textureName);

   private:
    std::vector<std::pair<std::string, sf::Texture>> textureList;  ///< List of textures and their names.
    std::vector<bool> isRevertList;                                ///< List indicating whether each texture in the textureList is reverted.
};
