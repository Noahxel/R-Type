#pragma once

#include "Component.hpp"

/**
 * @class PositionComponent
 * @brief Component that stores the position of an entity.
 *
 * This component holds the x and y coordinates for the position of an entity
 * in the game world. It is derived from the Component base class.
 */
class PositionComponent : public Component {
   public:
    float x;  ///< X coordinate of the entity in the game world
    float y;  ///< Y coordinate of the entity in the game world

    /**
     * @brief Construct a new Position Component object
     *
     * @param x Initial x coordinate of the entity
     * @param y Initial y coordinate of the entity
     */
    PositionComponent(float x, float y) : x(x), y(y) {}
};

/**
 * @class HitboxComponent
 * @brief Component that stores the hitbox dimensions of an entity.
 *
 * This component defines the width and height of the hitbox for an entity.
 * It is used for collision detection purposes and is derived from the Component
 * base class.
 */
class HitboxComponent : public Component {
   public:
    float width;   ///< Width of the hitbox
    float height;  ///< Height of the hitbox

    /**
     * @brief Construct a new Hitbox Component object
     *
     * @param w Width of the hitbox
     * @param h Height of the hitbox
     */
    HitboxComponent(float w, float h) : width(w), height(h) {}
};

/**
 * @class PlayerComponent
 * @brief Component that represents player-specific data.
 *
 * This component holds data specific to players, such as the client ID and
 * whether the player is active in the game. It is derived from the Component
 * base class.
 */
class PlayerComponent : public Component {
   public:
    int clientId;   ///< Unique identifier for the client associated with the player
    bool isActive;  ///< Flag indicating whether the player is active

    /**
     * @brief Construct a new Player Component object
     *
     * @param clientId The unique identifier for the client
     */
    PlayerComponent(int clientId) : clientId(clientId), isActive(true) {}
};
