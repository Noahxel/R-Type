#pragma once

/**
 * @class Entity
 * @brief Represents a unique entity in the ECS.
 *
 * This class encapsulates an entity in the Entity Component System (ECS),
 * which is essentially a unique identifier that can be associated with
 * various components to represent objects in the game world.
 */
class Entity {
   public:
    /**
     * @brief Construct a new Entity object with a unique identifier.
     *
     * @param id The unique identifier for the entity.
     */
    explicit Entity(int id) : id_(id) {}

    /**
     * @brief Get the unique identifier for the entity.
     *
     * @return The identifier of the entity as an integer.
     */
    int id() const { return id_; }

   private:
    int id_;  ///< The unique identifier for the entity
};
