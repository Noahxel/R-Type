#pragma once

/**
 * @interface ISystem
 * @brief Interface for ECS systems.
 *
 * Systems contain the logic to process entities and their components. They operate on
 * entities that have a specific set of components required by the system.
 */
class ISystem {
public:
    /**
     * @brief Update the system, processing its entities and components.
     * @param dt Delta time since the last update call.
     */
    virtual void update(float dt) = 0;

    /**
     * @brief Virtual destructor for interface cleanup.
     */
    virtual ~ISystem() = default;
};
