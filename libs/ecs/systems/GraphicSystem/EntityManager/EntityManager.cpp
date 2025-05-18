#include "EntityManager.hpp"

/**
 * @brief Get the index of an entity in the server's entity list by its ID.
 *
 * @param entityId The unique identifier of the entity.
 * @return int The index of the entity in the server's entity list, or -1 if not found.
 */
int EntityManager::getIndex(int entityId) {
    for (size_t i = 0, size = serverEntitiesId.size(); i < size; i++) {
        if (serverEntitiesId[i].first == entityId) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * @brief Get the lowest ID currently assigned to an entity.
 *
 * @return int The lowest entity ID.
 */
int EntityManager::getLowestId() {
    auto minElement = std::min_element(serverEntitiesId.begin(), serverEntitiesId.end());

    return minElement->first;
}

/**
 * @brief Add a new entity to the server's entity list.
 *
 * @param serverEntity The unique identifier for the new entity.
 * @param entityType The type of the entity (e.g., "Player", "Enemy").
 */
void EntityManager::addEntity(int serverEntity, std::string entityType) {
    std::pair<int, std::string> pair = std::make_pair(serverEntity, entityType);
    if (serverEntity == -1) {
        pair.first = getLowestId() - 1;
    }
    serverEntitiesId.push_back(pair);
}

/**
 * @brief Get the type of an entity based on its server ID.
 *
 * @param serverEntity The unique identifier of the entity.
 * @return std::string The type of the entity.
 */
std::string EntityManager::getEntityType(int serverEntity) {
    int entityId = getIndex(serverEntity);

    return serverEntitiesId[entityId].second;
}

/**
 * @brief Remove an entity from the server's entity list by its ID.
 *
 * @param entityId The unique identifier of the entity to remove.
 */
void EntityManager::removeEntity(int entityId) {
    int entityRegistryPos = getIndex(entityId);

    serverEntitiesId.erase(serverEntitiesId.begin() + entityRegistryPos);
}

/**
 * @brief Add a new player entity and get the color identifier for the player sprite.
 *
 * @return int The color identifier for the new player.
 */
int EntityManager::addPlayerAndGetColor() {
    playerCount++;
    if (playerCount == 6)
        playerCount = 0;
    return playerCount;
}
