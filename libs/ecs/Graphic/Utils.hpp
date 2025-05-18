#pragma once
#include <type_traits>

/**
 * @namespace Utils
 * @brief A utility namespace for common helper functions and structures.
 */
namespace Utils {

/**
 * @brief Converts an enumeration type to its underlying integral type.
 * 
 * @tparam Enum The enumeration type to be converted.
 * @param e The enumeration value to be converted.
 * @return The underlying integral value of the enumeration.
 */
template <typename Enum>
constexpr auto to_underlying(Enum e) -> typename std::underlying_type<Enum>::type {
    return static_cast<typename std::underlying_type<Enum>::type>(e);
}

/**
 * @struct Vec2
 * @brief A structure to represent two-dimensional vectors or coordinates.
 *
 * This structure provides a simple representation of 2D vectors, commonly used for positions,
 * velocities, scales, etc., in a 2D space.
 */
struct Vec2 {
    float x = 0.0f;  ///< The x component of the vector.
    float y = 0.0f;  ///< The y component of the vector.

    /**
     * @brief Construct a new Vec2 object with default values.
     */
    Vec2() = default;

    /**
     * @brief Construct a new Vec2 object with specified x and y components.
     * 
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     */
    Vec2(float x, float y) : x(x), y(y) {}

    /**
     * @brief Equality comparison operator.
     *
     * Compares two Vec2 objects for equality. Returns true if both x and y components are equal.
     * 
     * @param other The Vec2 object to compare with.
     * @return True if the Vec2 objects are equal, false otherwise.
     */
    bool operator==(const Vec2& other) const { return x == other.x && y == other.y; }

    /**
     * @brief Inequality comparison operator.
     *
     * Compares two Vec2 objects for inequality. Returns true if either x or y components are not equal.
     * 
     * @param other The Vec2 object to compare with.
     * @return True if the Vec2 objects are not equal, false otherwise.
     */
    bool operator!=(const Vec2& other) const { return x != other.x || y != other.y; }
};

/**
 * @struct PlayerId
 * @brief A structure to represent player identifiers and their positions.
 *
 * This structure encapsulates the identifier of a player along with their position in a 2D space.
 */
struct PlayerId {
    std::size_t id = 0;  ///< The unique identifier of the player.
    Vec2 pos;            ///< The 2D position of the player.

    /**
     * @brief Construct a new PlayerId object with an identifier and position.
     * 
     * @param id The unique identifier of the player.
     * @param pos The 2D position of the player.
     */
    PlayerId(std::size_t id, Vec2 pos) : id(id), pos(pos) {}
};

}  // namespace Utils
