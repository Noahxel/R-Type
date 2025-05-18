#include "SpriteSystem.hpp"

/**
 * @brief Sets properties for a sprite component using the provided texture.
 *
 * @param sprite Reference to the SpriteComponent to modify.
 * @param texture Reference to the SFML Texture to apply to the sprite.
 */
void SpriteSystem::setSpriteProperties(SpriteComponent& sprite, sf::Texture& texture) {
    sprite.sprite = sf::Sprite();
    sprite.sprite.setTexture(texture);
};

/**
 * @brief Draws the specified sprite component on the given window.
 *
 * @param window Pointer to the SFML RenderWindow where the sprite will be drawn.
 * @param sprite Reference to the SpriteComponent to draw.
 */
void SpriteSystem::draw(sf::RenderWindow* window, SpriteComponent& sprite) {
    window->draw(sprite.sprite);
};

/**
 * @brief Sets the texture rectangle for the sprite component, defining the area of the texture to display.
 *
 * @param sprite Reference to the SpriteComponent to modify.
 * @param rect The SFML IntRect representing the area of the texture to use.
 */
void SpriteSystem::setSpriteRect(SpriteComponent& sprite, sf::IntRect rect) {
    (void)sprite;
    sprite.sprite.setTextureRect(rect);
};

/**
 * @brief Sets the position of the sprite component.
 *
 * @param sprite Reference to the SpriteComponent to modify.
 * @param pos The Utils::Vec2 object representing the new position.
 */
void SpriteSystem::setSpritePos(SpriteComponent& sprite, Utils::Vec2& pos) {
    sprite.sprite.setPosition(pos.x, pos.y);
};

/**
 * @brief Sets the scale of the sprite component based on the provided scale component.
 *
 * @param sprite Reference to the SpriteComponent to modify.
 * @param sc The ScaleComponent containing the scale values to apply.
 */
void SpriteSystem::setSpriteScale(SpriteComponent& sprite, ScaleComponent& sc) {
    sprite.sprite.setScale(sf::Vector2f(sc.scale.x, sc.scale.y));
};
