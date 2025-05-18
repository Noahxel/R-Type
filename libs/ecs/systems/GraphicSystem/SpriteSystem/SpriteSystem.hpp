#pragma once

#include "../../../Graphic/GraphicComponents.hpp"

/**
 * @class SpriteSystem
 * @brief System to handle sprite-related operations within the game.
 *
 * This class is responsible for managing various aspects of sprite components, such as
 * setting properties, drawing them on the screen, and adjusting their attributes like
 * position, scale, and texture rectangle.
 */
class SpriteSystem {
   public:
    /**
     * @brief Sets the properties of a sprite component using a given texture.
     * 
     * @param sprite Reference to the SpriteComponent to modify.
     * @param texture Reference to the SFML Texture to apply to the sprite.
     */
    void setSpriteProperties(SpriteComponent& sprite, sf::Texture& texture);

    /**
     * @brief Draws the specified sprite component on the provided SFML RenderWindow.
     * 
     * @param window Pointer to the SFML RenderWindow where the sprite is to be drawn.
     * @param sprite Reference to the SpriteComponent to be drawn.
     */
    void draw(sf::RenderWindow* window, SpriteComponent& sprite);

    /**
     * @brief Sets the texture rectangle for a sprite component, defining the area of the texture to display.
     * 
     * @param sprite Reference to the SpriteComponent to modify.
     * @param rect The SFML IntRect representing the texture area to use for the sprite.
     */
    void setSpriteRect(SpriteComponent& sprite, sf::IntRect rect);

    /**
     * @brief Sets the position of the sprite component.
     * 
     * @param sprite Reference to the SpriteComponent to modify.
     * @param pos The Utils::Vec2 object representing the new position coordinates.
     */
    void setSpritePos(SpriteComponent& sprite, Utils::Vec2& pos);

    /**
     * @brief Sets the scale of the sprite component based on the provided scale component.
     * 
     * @param sprite Reference to the SpriteComponent to modify.
     * @param sc The ScaleComponent containing the scale values to apply to the sprite.
     */
    void setSpriteScale(SpriteComponent& sprite, ScaleComponent& sc);
};
