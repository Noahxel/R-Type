#pragma once

#include <memory>

/**
 * @class Component
 * @brief Abstract base class for components in the ECS.
 *
 * This class serves as a base for all components in the Entity Component System.
 * It provides the interface that all derived components should follow. Components
 * are meant to store data for entities and should not contain logic.
 */
class Component {
   public:
    /**
     * @brief Virtual destructor for the Component class.
     *
     * Ensures that derived classes can be cleaned up correctly when deleted.
     */
    virtual ~Component() = default;
};
