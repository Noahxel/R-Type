#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

/**
 * @struct PairHash
 * @brief Custom hash function object for pairs of type_index and int.
 *
 * This structure is a functional object (providing operator()) that generates a hash value for pairs.
 * It is particularly used for hashing pairs consisting of a type_index and an int, which is a common
 * pattern in entity-component systems for associating components with entities.
 */
struct PairHash {
    /**
     * @brief Generates a hash value for a std::pair<std::type_index, int>.
     *
     * Combines the hash of the type_index and int from the pair to create a unique hash value.
     *
     * @param pair The pair of std::type_index and int to be hashed.
     * @return std::size_t The resulting hash value.
     */
    std::size_t operator()(const std::pair<std::type_index, int>& pair) const {
        return std::hash<std::type_index>()(pair.first) ^ std::hash<int>()(pair.second);
    }
};
