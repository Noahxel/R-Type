#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "../../Graphic/GraphicComponents.hpp"
#include "AnimationSystem/AnimationSystem.hpp"
#include "EntityManager/EntityManager.hpp"
#include "EventSystem/EventSystem.hpp"
#include "GameOverSystem/GameOverSystem.hpp"
#include "SpriteSystem/SpriteSystem.hpp"
#include "TextureLoader/TextureLoader.hpp"

/**
 * @class GraphicSystem
 * @brief Manages the rendering and graphical components of the game.
 *
 * This class encapsulates the functionality for rendering game elements, managing textures,
 * handling animations, and responding to game events. It also manages the game over state.
 */
class GraphicSystem {
   public:
    /**
     * @brief Constructs a GraphicSystem object with a specified window size.
     * 
     * @param windowWidth Width of the game window.
     * @param windowHeight Height of the game window.
     */
    GraphicSystem(int windowWidth, int windowHeight);

    /**
     * @brief Displays all graphical elements on the game window.
     */
    void displayAll();

    /**
     * @brief Factory method for creating and initializing entities within the game.
     * 
     * @param entityId The ID of the entity to create.
     * @param entityType The type of the entity (e.g., "Player", "Enemy").
     * @param relatedEntityPosId Optional ID for positioning relative to another entity.
     */
    void factory(int entityId, std::string entityType, int relatedEntityPosId = -1);

    /**
     * @brief Sets the position of a specific entity in the game.
     * 
     * @param x The x-coordinate of the new position.
     * @param y The y-coordinate of the new position.
     * @param entityId The ID of the entity whose position is being set.
     */
    void setNewPos(float x, float y, int entityId);

    /**
     * @brief Removes a specific entity from the game.
     * 
     * @param entityId The ID of the entity to remove.
     */
    void removeEntity(int entityId);

    /**
     * @brief Refreshes the game graphics, updating sprites, positions, and animations.
     */
    void refreshGame();

    ComponentManager cm;              ///< Component manager for ECS.
    EntityManager em;                 ///< Entity manager for ECS.
    sf::RenderWindow* window;         ///< SFML window for rendering.
    TextureLoader textureLoader;      ///< Manages textures for sprites.
    SpriteSystem spriteSystem;        ///< Manages sprite operations.
    AnimationSystem animationSystem;  ///< Manages animations for entities.
    EventSystem eventSystem;          ///< Handles game events.
    GameOverSystem gameOverSystem;    ///< Manages the game over state.
    bool isGameOver;                  ///< Flag indicating if the game is over.
};
