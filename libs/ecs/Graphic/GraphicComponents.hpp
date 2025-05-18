#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "ComponentManager.hpp"
#include "Utils.hpp"

/**
 * @class SpriteComponent
 * @brief Component for handling SFML sprites.
 *
 * This component encapsulates an SFML sprite, allowing entities to have a visual representation.
 */
class SpriteComponent {
   public:
    sf::Sprite sprite;  ///< The SFML sprite object.
};

/**
 * @class PosComponent
 * @brief Component for handling position.
 *
 * This component stores the x and y coordinates, representing the position of an entity in the game world.
 */
class PosComponent {
   public:
    /**
     * @brief Construct a new Position Component object with default coordinates.
     *
     * @param defaultX The default x-coordinate.
     * @param defaultY The default y-coordinate.
     */
    PosComponent(float defaultX = 0, float defaultY = 0) : coord(defaultX, defaultY) {}

    /**
     * @brief Construct a new Position Component object with a vector.
     *
     * @param vec A vector containing the x and y coordinates.
     */
    explicit PosComponent(const Utils::Vec2& vec) : coord(vec) {}

    Utils::Vec2 coord;  ///< The coordinates of the entity.
};

/**
 * @class ScaleComponent
 * @brief Component for handling scaling of entities.
 *
 * This component stores the scale factors along the x and y axes.
 */
class ScaleComponent {
   public:
    /**
     * @brief Construct a new Scale Component object with vector scaling.
     *
     * @param v A vector containing the scale factors for x and y axes.
     */
    ScaleComponent(Utils::Vec2 v = {1, 1}) : scale(v){};

    /**
     * @brief Construct a new Scale Component object with individual scale factors.
     *
     * @param x Scale factor along the x-axis.
     * @param y Scale factor along the y-axis.
     */
    explicit ScaleComponent(float x = 1, float y = 1) : scale(x, y){};

    Utils::Vec2 scale;  ///< The scale factors of the entity.
};

/**
 * @class AnimationComponent
 * @brief Component for handling animations.
 *
 * This component stores animation-related data, such as the current step, maximum steps,
 * and the speed of the animation.
 */
class AnimationComponent {
   public:
    /**
     * @brief Construct a new Animation Component object.
     *
     * @param step The initial step of the animation.
     * @param maxStep The maximum step of the animation.
     * @param animationSpeed The speed of the animation.
     */
    AnimationComponent(int step, int maxStep, int animationSpeed)
        : step_value(step), max_step(maxStep), animation_speed(animationSpeed), isAnimatedToRight(true), haveLoopedOnce(false) {}

    int step_value;                                                           ///< The current step of the animation.
    int max_step;                                                             ///< The maximum step of the animation.
    int animation_speed;                                                      ///< The speed of the animation.
    int last_step;                                                            ///< The last step of the animation that was processed.
    std::chrono::high_resolution_clock::time_point last_animation_step_time;  ///< The time point of the last animation step.
    sf::IntRect textureRect;                                                  ///< The texture rectangle for the sprite sheet.
    bool isReverted;         ///< Do the texture have to loop on itself to be animated (right to left then left to right).
    bool isAnimatedToRight;  ///< Current animation direction
    bool haveLoopedOnce;     ///< Do the animation already looped once;
};
