#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <typeindex>
#include <unordered_map>
#include "Components.hpp"
#include "PairHash.hpp"
#include "System.hpp"

/**
 * @class EnemyMovementSystem
 * @brief System to handle the movement behavior of enemy entities.
 *
 * This system updates the position of enemy entities based on a set speed.
 * Enemies move horizontally across the screen and reappear on the other side
 * once they go off-screen, with a random Y position within the maximum bounds.
 */
class EnemyMovementSystem : public System {
   public:
    /**
     * @brief Construct a new Enemy Movement System object.
     *
     * @param initialX The X coordinate from which the enemies will start.
     * @param offScreenX The X coordinate at which enemies are considered off-screen.
     * @param speed The horizontal speed of the enemies.
     * @param maxY The maximum Y coordinate that enemies can randomly reappear at.
     */
    EnemyMovementSystem(float initialX, float offScreenX, float speed, float maxY)
        : initialX_(initialX), offScreenX_(offScreenX), speed_(speed), maxY_(maxY) {}

    /**
     * @brief Update the position of enemy entities within the system.
     *
     * @param dt Delta time to control the movement speed based on time rather than frames.
     * @param components A reference to the map storing all components associated with their entity IDs.
     */
    void update(float dt, std::unordered_map<std::pair<std::type_index, int>, std::shared_ptr<Component>, PairHash>& components) override {
        for (auto& pair : components) {
            if (pair.first.first == typeid(PositionComponent)) {
                auto entityId = pair.first.second;
                if (components.count({typeid(HitboxComponent), entityId}) > 0 && components.count({typeid(PlayerComponent), entityId}) == 0) {
                    auto posComp = std::dynamic_pointer_cast<PositionComponent>(pair.second);

                    posComp->x -= speed_ * dt;

                    if (posComp->x < offScreenX_) {
                        posComp->x = initialX_;
                        posComp->y = getRandomY();
                    }
                }
            }
        }
    }

   private:
    float initialX_;    ///< Starting X coordinate for enemies
    float offScreenX_;  ///< X coordinate at which enemies are considered to have gone off-screen
    float speed_;       ///< Horizontal speed of the enemies
    float maxY_;        ///< Maximum Y coordinate for enemy repositioning

    /**
     * @brief Generates a random Y coordinate within the maximum bounds.
     *
     * @return A random float value representing the Y coordinate.
     */
    float getRandomY() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, maxY_);
        return dis(gen);
    }
};
