#pragma once

#include "../../../Graphic/GraphicComponents.hpp"

/**
 * @class EntityManager
 * @brief Manages the lifecycle and properties of entities in the game.
 *
 * This class is responsible for keeping track of all entities in the game, assigning unique identifiers,
 * and associating them with their respective types.
 */
class EntityManager {
   public:
    /**
     * @brief Add a new entity to the manager with a specified type.
     * 
     * @param serverEntity The unique identifier for the new entity.
     * @param entityType The type of the new entity (e.g., "Player", "Enemy").
     */
    void addEntity(int serverEntity, std::string entityType);

    /**
     * @brief Remove an entity from the manager using its unique identifier.
     * 
     * @param entityId The unique identifier of the entity to remove.
     */
    void removeEntity(int entityId);

    /**
     * @brief Retrieve the index of an entity in the manager's list using its unique identifier.
     * 
     * @param entityId The unique identifier of the entity.
     * @return int The index of the entity in the list, or -1 if not found.
     */
    int getIndex(int entityId);

    /**
     * @brief Add a player entity and assign a unique color based on the player count.
     * 
     * @return int A unique color identifier for the player entity.
     */
    int addPlayerAndGetColor();

    /**
     * @brief Get the type of an entity based on its unique identifier.
     * 
     * @param serverEntity The unique identifier of the entity.
     * @return std::string The type of the entity.
     */
    std::string getEntityType(int serverEntity);

    /**
     * @brief Get the lowest unused unique identifier for new entities.
     * 
     * @return int The lowest available unique identifier.
     */
    int getLowestId();

    std::vector<std::pair<int, std::string>>
        serverEntitiesId;  ///< A vector of pairs, where each pair contains an entity's unique identifier and its type.
    int playerCount;       ///< The count of players currently in the game, used to assign unique colors to player entities.
};
