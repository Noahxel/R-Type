#pragma once
#include <cstddef>

/**
 * @class UniqueEntity
 * @brief Represents a unique identifier for entities in an ECS.
 *
 * This class encapsulates an entity identifier, providing a type-safe way of handling entity IDs.
 * The identifier can be implicitly converted to a size_t type, and arithmetic operations are supported.
 */
class UniqueEntity {
   public:
    /**
     * @brief Construct a new Unique Entity object
     * 
     * @param id The unique identifier for the entity.
     */
    explicit UniqueEntity(size_t id) : _id(id) {}

    /**
     * @brief Implicit conversion to size_t.
     * 
     * @return The underlying size_t identifier.
     */
    operator size_t() const { return _id; }

    /**
     * @brief Addition operator for UniqueEntity.
     * 
     * @param entity The UniqueEntity to add to.
     * @param value The value to add to the entity's ID.
     * @return A new UniqueEntity with the resulting ID.
     */
    friend inline UniqueEntity operator+(const UniqueEntity& entity, size_t value);

    /**
     * @brief Subtraction operator for UniqueEntity.
     * 
     * @param entity The UniqueEntity to subtract from.
     * @param value The value to subtract from the entity's ID.
     * @return A new UniqueEntity with the resulting ID.
     */
    friend inline UniqueEntity operator-(const UniqueEntity& entity, size_t value);

    /**
     * @brief Multiplication operator for UniqueEntity.
     * 
     * @param entity The UniqueEntity to multiply.
     * @param value The value to multiply the entity's ID by.
     * @return A new UniqueEntity with the resulting ID.
     */
    friend inline UniqueEntity operator*(const UniqueEntity& entity, size_t value);

   private:
    size_t _id;  ///< The unique identifier of the entity.
};

inline UniqueEntity operator+(const UniqueEntity& entity, size_t value) {
    return UniqueEntity(entity._id + value);
}

inline UniqueEntity operator-(const UniqueEntity& entity, size_t value) {
    return UniqueEntity(entity._id - value);
}

inline UniqueEntity operator*(const UniqueEntity& entity, size_t value) {
    return UniqueEntity(entity._id * value);
}
