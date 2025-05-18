#pragma once

#include <memory>
#include <vector>
#include "IComponent.hpp"

/**
 * @interface IEntity
 * @brief Interface for ECS entities.
 *
 * Entities are containers for components and do not contain any data or logic themselves.
 * They act as identifiers to group related components together.
 */
class IEntity {
public:
    /**
     * @brief Get the entity's unique identifier.
     * @return A unique identifier for the entity.
     */
    virtual int getId() const = 0;

    /**
     * @brief Add a component to the entity.
     * @param component Shared pointer to the component to add.
     */
    virtual void addComponent(std::shared_ptr<IComponent> component) = 0;

    /**
     * @brief Get a component of a specific type from the entity.
     * @return Shared pointer to the requested component type, or nullptr if not found.
     */
    virtual std::shared_ptr<IComponent> getComponent() const = 0;

    /**
     * @brief Virtual destructor for interface cleanup.
     */
    virtual ~IEntity() = default;
};
