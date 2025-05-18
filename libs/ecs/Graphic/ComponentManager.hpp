#pragma once

#include <any>
#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <unordered_map>
#include "SparseArray.hpp"
#include "UniqueEntity.hpp"

/**
 * @class ComponentManager
 * @brief Manages the registration and handling of components for entities in an ECS.
 *
 * This class provides the functionality to add, remove, and retrieve components for entities.
 * It uses SparseArray to store components efficiently. Systems can be added to operate on
 * components of entities. It also handles the creation and destruction of entities.
 */
class ComponentManager {
   public:
    std::size_t gameState;  ///< Represents the state of the game, used to control the flow of the ECS.

    /**
     * @brief Registers a component type to the manager and returns a reference to its SparseArray.
     * 
     * @tparam T The component type to register.
     * @return Reference to the SparseArray managing the component type T.
     */
    template <typename T>
    SparseArray<T>& registerComponent() {
        auto [iter, isNew] = SparseArrays.try_emplace(typeid(T), SparseArray<T>(maxEntityId));
        if (isNew) {
            removeEntityFunctions[typeid(T)] = &ComponentManager::removeEntity<T>;
            addEntityFunctions[typeid(T)] = &ComponentManager::addEntity<T>;
        }
        return std::any_cast<SparseArray<T>&>(iter->second);
    }

    /**
     * @brief Registers multiple component types at once and returns a tuple of references to their SparseArrays.
     * 
     * @tparam T The component types to register.
     * @return Tuple of references to the SparseArrays managing the component types.
     */
    template <typename... T>
    std::tuple<SparseArray<T>&...> registerComponents() {
        return std::tie(registerComponent<T>()...);
    }

    /**
     * @brief Retrieves the SparseArray for a specific component type.
     * 
     * @tparam T The component type to retrieve.
     * @return Reference to the SparseArray managing the component type T.
     */
    template <typename T>
    SparseArray<T>& getSparseArray() {
        try {
            return std::any_cast<SparseArray<T>&>(SparseArrays.at(typeid(T)));
        } catch (const std::bad_any_cast&) {
            std::cerr << "Component not registered: " << typeid(T).name() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    /**
     * @brief Retrieves the SparseArray for a specific component type (const version).
     * 
     * @tparam T The component type to retrieve.
     * @return Const reference to the SparseArray managing the component type T.
     */
    template <typename T>
    const SparseArray<T>& getSparseArray() const {
        return std::any_cast<const SparseArray<T>&>(SparseArrays.at(typeid(T)));
    }

    /**
     * @brief Adds a component to an entity.
     * 
     * @tparam T The type of component to add.
     * @param to The entity to add the component to.
     * @param component The component instance to add.
     * @return Reference to the added component within the SparseArray.
     */
    template <typename T>
    typename SparseArray<T>::reference addComponent(const UniqueEntity& to, T&& component) {
        auto& compSet = getSparseArray<T>();
        compSet[static_cast<size_t>(to)] = std::forward<T>(component);
        return compSet[static_cast<size_t>(to)];
    }

    /**
     * @brief Emplaces a component to an entity using constructor parameters.
     * 
     * @tparam T The type of component to emplace.
     * @tparam Params The parameter pack for the component's constructor.
     * @param to The entity to emplace the component to.
     * @param params The parameters for constructing the component.
     * @return Reference to the emplaced component within the SparseArray.
     */
    template <typename T, typename... Params>
    typename SparseArray<T>::reference emplaceComponent(const UniqueEntity& to, Params&&... params) {
        auto& compSet = getSparseArray<T>();
        compSet[static_cast<size_t>(to)] = std::make_optional<T>(std::forward<Params>(params)...);
        return compSet[static_cast<size_t>(to)];
    }

    /**
     * @brief Removes a component from an entity.
     * 
     * @tparam T The type of component to remove.
     * @param from The entity to remove the component from.
     */
    template <typename T>
    void removeComponent(const UniqueEntity& from) {
        removeEntityFunctions[std::type_index(typeid(T))](std::ref(*this), from);
    }

    /**
     * @brief Adds a system to the manager that operates on specified component types.
     * 
     * @tparam Components The types of components the system operates on.
     * @tparam Function The type of the function that implements the system's logic.
     * @param function The system function to add.
     */
    template <typename... Components, typename Function>
    void addSystem(Function&& function) {
        auto lambda = [&](ComponentManager& manager) {
            function(manager, manager.getSparseArray<Components>()...);
        };
        systems.push_back(lambda);
    }

    /**
     * @brief Adds a system to the manager that operates on specified component types (const version).
     * 
     * @tparam Components The types of components the system operates on.
     * @tparam Function The type of the function that implements the system's logic.
     * @param function The system function to add.
     */
    template <typename... Components, typename Function>
    void addSystem(const Function& function) {
        auto lambda = [&](ComponentManager& manager) {
            function(manager, manager.getSparseArray<Components>()...);
        };
        systems.push_back(lambda);
    }

    /**
     * @brief Creates a new entity and returns its UniqueEntity identifier.
     * 
     * @return The UniqueEntity identifier of the newly created entity.
     */
    UniqueEntity createEntity() {
        for (const auto& [key, _] : SparseArrays) {
            addEntityFunctions[key](*this, maxEntityId);
        }
        return UniqueEntity(maxEntityId++);
    }

    /**
     * @brief Creates a UniqueEntity identifier from an index.
     * 
     * @param idx The index to create a UniqueEntity identifier from.
     * @return The UniqueEntity identifier created from the index.
     */
    UniqueEntity createEntityIndex(size_t idx) { return UniqueEntity(idx); }

    /**
     * @brief Destroys an entity and removes all associated components.
     * 
     * @param entity The entity to destroy.
     */
    void destroyEntity(const UniqueEntity& entity) {
        for (auto& [key, _] : SparseArrays)
            removeEntityFunctions[key](std::ref(*this), entity);
    }

    /**
     * @brief Destroys all entities and their associated components.
     */
    void destroyAllEntities() {
        for (const auto& [key, _] : SparseArrays) {
            for (size_t i = 0; i < maxEntityId; ++i) {
                removeEntityFunctions[key](*this, UniqueEntity(i));
            }
        }
        maxEntityId = 0;
    }

    /**
     * @brief Executes all systems added to the manager.
     */
    void executeSystems() {
        for (auto& system : systems)
            system(std::ref(*this));
    }

   private:
    std::unordered_map<std::type_index, std::any> SparseArrays;  ///< Stores SparseArrays for each component type.
    std::unordered_map<std::type_index, std::function<void(ComponentManager&, const UniqueEntity&)>>
        removeEntityFunctions;  ///< Maps component types to their entity removal functions.
    std::unordered_map<std::type_index, std::function<void(ComponentManager&, size_t)>>
        addEntityFunctions;                                       ///< Maps component types to their entity addition functions.
    std::vector<std::function<void(ComponentManager&)>> systems;  ///< Stores functions representing systems to be executed.
    size_t maxEntityId = 0;                                       ///< The maximum entity ID used to generate new entity identifiers.

    /**
     * @brief Helper function to remove a specific entity's component of type T.
     * 
     * @tparam T The component type to remove.
     * @param entity The entity to remove the component from.
     */
    template <typename T>
    void removeEntity(const UniqueEntity& entity) {
        auto& comp = std::any_cast<SparseArray<T>&>(SparseArrays[typeid(T)]);
        comp.remove(static_cast<size_t>(entity));
    }

    /**
     * @brief Helper function to add a new entity's component placeholder of type T.
     * 
     * @tparam T The component type to add.
     * @param entity The entity index to add the component placeholder for.
     */
    template <typename T>
    void addEntity(size_t entity) {
        auto& comp = std::any_cast<SparseArray<T>&>(SparseArrays[typeid(T)]);
        comp.add(entity);
    }
};
