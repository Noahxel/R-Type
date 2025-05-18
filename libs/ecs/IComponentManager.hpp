#pragma once

#include <typeindex>
#include <unordered_map>
#include "IComponent.hpp"

/**
 * @interface IComponentManager
 * @brief Interface for managing ECS components.
 *
 * Provides functionality to add, retrieve, and manage components associated with entities.
 */
class IComponentManager {
public:
    /**
     * @brief Register a new component type with the manager.
     * @tparam T The component type to register.
     */
    template<typename T>
    void registerComponent();

    /**
     * @brief Add a component to an entity.
     * @param entityId The ID of the entity to add the component to.
     * @param component Shared pointer to the component to add.
     */
    virtual void addComponent(int entityId, std::shared_ptr<IComponent> component) = 0;

    /**
     * @brief Get a component of a specific type associated with an entity.
     * @param entityId The ID of the entity to retrieve the component from.
     * @return Shared pointer to the requested component type, or nullptr if not found.
     */
    virtual std::shared_ptr<IComponent> getComponent(int entityId) = 0;

    /**
     * @brief Virtual destructor for interface cleanup.
     */
    virtual ~IComponentManager() = default;
};
