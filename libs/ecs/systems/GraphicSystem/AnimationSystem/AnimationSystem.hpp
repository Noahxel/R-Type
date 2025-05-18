#pragma once

#include "../../../Graphic/GraphicComponents.hpp"
#include "../EntityManager/EntityManager.hpp"

/**
 * @class AnimationSystem
 * @brief System to handle animations within the ECS framework.
 *
 * This class provides functionality to animate entities, manage flash animations,
 * and track animation relationships between entities.
 */
class AnimationSystem {
   public:
    /**
     * @brief Animates an entity's sprite based on the AnimationComponent.
     *
     * @param animationElem The AnimationComponent of the entity to be animated.
     */
    void AnimateElem(AnimationComponent& animationElem);

    /**
     * @brief Associates a flash animation entity with another entity.
     *
     * @param relatedEntityId ID of the entity related to the flash animation.
     * @param flashEntityId ID of the flash animation entity.
     */
    void addRelatedEntityFlash(int relatedEntityId, int flashEntityId);

    /**
     * @brief Retrieves the flash animation entity related to the specified entity ID.
     *
     * @param flashEntityId ID of the flash animation entity.
     * @return int The related entity's ID or -1 if not found.
     */
    int getRelatedEntityFlash(int flashEntityId);

    /**
     * @brief Removes the association of a flash animation entity with another entity.
     *
     * @param flashEntityId ID of the flash animation entity to disassociate.
     */
    void removeRelatedEntityFlash(int flashEntityId);

    /**
     * @brief Checks if the specified entity already has a flash animation of a given type.
     *
     * @param relatedEntityId ID of the entity to check.
     * @param flashAnimType Type of the flash animation to check for.
     * @param serverEntitiesId Reference to the EntityManager managing entities.
     * @return true If a flash animation of the specified type exists.
     * @return false Otherwise.
     */
    bool doEntityAlreadyHaveFlash(int relatedEntityId, std::string flashAnimType, EntityManager& serverEntitiesId);

    /**
     * @brief Retrieves all flash animation entity IDs related to a specific entity.
     * 
     * @param entityId ID of the entity for which to find all related flash animations.
     * @return std::vector<int> Vector containing all related flash animation entity IDs.
     */
    std::vector<int> getAllFlashByEntity(int entityId);

    std::vector<std::pair<int, int>> relatedIdFlashAnimations;  ///< Stores pairs of entity IDs and their associated flash animation entity IDs.
};
