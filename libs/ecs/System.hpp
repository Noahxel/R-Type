#pragma once

#include <typeindex>
#include <unordered_map>
#include "Component.hpp"
#include "Entity.hpp"
#include "PairHash.hpp"

/**
 * @class System
 * @brief Abstract base class for systems in the ECS framework.
 *
 * Systems are responsible for updating the components of entities. Each system
 * will have an update method that will be called every frame and will handle
 * the logic for a specific aspect of the game, such as rendering or movement.
 */
class System {
   public:
    /**
     * @brief Virtual update method to be implemented by derived systems.
     *
     * This method will contain the logic to update entities based on their components.
     * It is called every frame with the time elapsed since the last frame, allowing
     * systems to perform time-based updates.
     *
     * @param dt Delta time since the last update call.
     * @param components A reference to the map storing all components associated with their entity IDs.
     */
    virtual void update(float dt, std::unordered_map<std::pair<std::type_index, int>, std::shared_ptr<Component>, PairHash>& components) = 0;
};
