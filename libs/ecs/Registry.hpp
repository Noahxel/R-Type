#pragma once

#include <algorithm>
#include <chrono>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "Components.hpp"
#include "Entity.hpp"
#include "PairHash.hpp"
#include "System.hpp"

/**
 * @class Registry
 * @brief Manages entities, components, and systems in the Entity Component System (ECS).
 *
 * This class serves as the central part of the ECS, handling the creation and management
 * of entities, associating components with entities, and orchestrating the update calls
 * to systems.
 */
class Registry {
   public:
    /**
     * @brief Construct a new Registry object.
     *
     * Initializes the entity ID counter and sets the last frame time to the current time.
     */
    Registry() : nextEntityId(1) { lastFrameTime = std::chrono::high_resolution_clock::now(); }

    /**
     * @brief Calculates and returns the time elapsed since the last frame.
     *
     * @return float The delta time in seconds.
     */
    float updateDeltaTime() {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - lastFrameTime).count();
        lastFrameTime = currentFrameTime;
        return deltaTime;
    }

    /**
     * @brief Creates a new entity and returns it.
     *
     * @return Entity The newly created entity.
     */
    Entity createEntity() {
        Entity newEntity(nextEntityId++);
        entities_.emplace_back(newEntity);
        return newEntity;
    }

    /**
     * @brief Returns a const reference to the list of entities.
     *
     * @return const std::vector<Entity>& A const reference to the entity list.
     */
    const std::vector<Entity>& getEntities() const { return entities_; }

    /**
     * @brief Adds a component of type T to an entity.
     *
     * @tparam T The component type.
     * @tparam Args The argument types for the component's constructor.
     * @param entity The entity to which the component will be added.
     * @param args The arguments for the component's constructor.
     */
    template <typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        components_[{typeid(T), entity.id()}] = component;
    }

    /**
     * @brief Retrieves the component of type T associated with an entity.
     *
     * @tparam T The component type.
     * @param entity The entity whose component is to be retrieved.
     * @return std::shared_ptr<T> A shared pointer to the component, or nullptr if not found.
     */
    template <typename T>
    std::shared_ptr<T> getComponent(Entity entity) {
        auto it = components_.find({typeid(T), entity.id()});
        if (it != components_.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    /**
     * @brief Adds a system to the registry.
     *
     * @param system A shared pointer to the system to be added.
     */
    void addSystem(std::shared_ptr<System> system) { systems_.push_back(system); }

    /**
     * @brief Updates all systems with the given delta time.
     *
     * @param dt The delta time since the last update in seconds.
     */
    void updateSystems(float dt) {
        for (auto& system : systems_) {
            system->update(dt, components_);
        }
    }

    /**
     * @brief Removes an entity from the registry.
     *
     * @param entityId The ID of the entity to be removed.
     */
    void removeEntity(int entityId) {
        entities_.erase(std::remove_if(entities_.begin(), entities_.end(), [entityId](const Entity& entity) { return entity.id() == entityId; }),
                        entities_.end());
    }

   private:
    std::vector<Entity> entities_;  ///< List of all entities.
    std::unordered_map<std::pair<std::type_index, int>, std::shared_ptr<Component>, PairHash>
        components_;                                               ///< Map of components associated with entities.
    std::vector<std::shared_ptr<System>> systems_;                 ///< List of all systems.
    int nextEntityId;                                              ///< The next available entity ID.
    std::chrono::high_resolution_clock::time_point lastFrameTime;  ///< Time point of the last frame update.
};
