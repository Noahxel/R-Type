#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include "Components.hpp"
#include "System.hpp"

/**
 * @class CollisionSystem
 * @brief Manages collision detection and response for entities in the game.
 *
 * This system checks for collisions between entities, particularly between players and enemies.
 * It uses position and hitbox components to determine collisions and triggers appropriate
 * responses such as game over callbacks.
 */
class CollisionSystem : public System {
   public:
    /**
     * @brief Construct a new Collision System object.
     *
     * @param gameOverCallback Callback function to be called when a collision resulting in game over is detected.
     * @param enemyEntityIds A set containing the IDs of enemy entities to check for collisions.
     * @param collisionThresholdX The horizontal threshold for collision detection.
     * @param collisionThresholdY The vertical threshold for collision detection.
     */
    CollisionSystem(std::function<void(int)> gameOverCallback, const std::set<int>& enemyEntityIds)
        : gameOverCallback_(gameOverCallback), enemyEntityIds_(enemyEntityIds) {}

    /**
     * @brief Update method overridden from System, checks for collisions between entities.
     *
     * @param dt Delta time since the last update call (not used in this system).
     * @param components A reference to the map storing all components associated with their entity IDs.
     */
    void update(float /*dt*/, std::unordered_map<std::pair<std::type_index, int>, std::shared_ptr<Component>, PairHash>& components) override {
        for (int enemyId : enemyEntityIds_) {
            checkCollisionsWithEnemy(enemyId, components);
        }
    }

    /**
     * @brief Checks for collisions between a specific enemy entity and all player entities.
     *
     * @param enemyId The ID of the enemy entity to check for collisions.
     * @param components A reference to the map storing all components associated with their entity IDs.
     */
    void checkCollisionsWithEnemy(int enemyId,
                                  std::unordered_map<std::pair<std::type_index, int>, std::shared_ptr<Component>, PairHash>& components) {
        auto enemyPosComp = std::dynamic_pointer_cast<PositionComponent>(components[{typeid(PositionComponent), enemyId}]);
        auto enemyHitboxComp = std::dynamic_pointer_cast<HitboxComponent>(components[{typeid(HitboxComponent), enemyId}]);

        if (!enemyPosComp || !enemyHitboxComp) {
            return;  // Enemy components not found, skip
        }

        for (auto& pair : components) {
            int playerId = -1;
            if (pair.first.first == typeid(PositionComponent) && pair.first.second != enemyId) {
                playerId = pair.first.second;
                auto playerPosComp = std::dynamic_pointer_cast<PositionComponent>(pair.second);
                auto playerHitboxComp = std::dynamic_pointer_cast<HitboxComponent>(components[{typeid(HitboxComponent), pair.first.second}]);

                if (playerPosComp && playerHitboxComp) {
                    if (isCollision(playerPosComp, playerHitboxComp, enemyPosComp, enemyHitboxComp)) {
                        if (processedCollisions_.find({playerId, enemyId}) == processedCollisions_.end()) {
                            // New collision detected, call the callback
                            gameOverCallback_(playerId);
                            // Mark this collision as processed
                            processedCollisions_.insert({playerId, enemyId});
                        }
                    } else {
                        // If there's no collision, remove from processed collisions
                        processedCollisions_.erase({playerId, enemyId});
                    }
                }
            }
        }
    }

    /**
     * @brief Determines if there is a collision between a player and an enemy entity.
     *
     * @param playerPosComp Position component of the player entity.
     * @param playerHitboxComp Hitbox component of the player entity.
     * @param enemyPosComp Position component of the enemy entity.
     * @param enemyHitboxComp Hitbox component of the enemy entity.
     * @return true if a collision is detected, false otherwise.
     */
    bool isCollision(std::shared_ptr<PositionComponent> playerPosComp, std::shared_ptr<HitboxComponent> playerHitboxComp,
                     std::shared_ptr<PositionComponent> enemyPosComp, std::shared_ptr<HitboxComponent> enemyHitboxComp) {
        return playerPosComp->x < enemyPosComp->x + enemyHitboxComp->width && playerPosComp->x + playerHitboxComp->width > enemyPosComp->x &&
               playerPosComp->y < enemyPosComp->y + enemyHitboxComp->height && playerPosComp->y + playerHitboxComp->height > enemyPosComp->y;
    }

    /**
     * @brief Updates the set of enemy entity IDs to be checked for collisions.
     *
     * @param enemyEntityIds The new set of enemy entity IDs.
     */
    void updateEnemyEntityIds(const std::set<int>& enemyEntityIds) { enemyEntityIds_ = enemyEntityIds; }

   private:
    std::function<void(int)> gameOverCallback_;          ///< Callback function for game over events.
    std::set<int> enemyEntityIds_;                       ///< Set of enemy entity IDs to check for collisions.
    std::set<std::pair<int, int>> processedCollisions_;  ///< Set of processed collisions to avoid repeated processing.
};
