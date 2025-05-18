#include "AnimationSystem.hpp"

/**
 * @brief Animate a single element if the elapsed time since the last animation step is greater than the animation speed.
 *
 * @param animationElem Reference to the AnimationComponent to animate.
 */
void AnimationSystem::AnimateElem(AnimationComponent& animationElem) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - animationElem.last_animation_step_time).count();

    if (elapsedMilliseconds >= animationElem.animation_speed) {
        if (animationElem.isAnimatedToRight) {
            if (animationElem.max_step <= animationElem.textureRect.left) {
                if (animationElem.isReverted) {
                    animationElem.isAnimatedToRight = false;
                } else {
                    animationElem.textureRect.left = 0;
                    animationElem.haveLoopedOnce = true;
                }
            } else {
                animationElem.textureRect.left += animationElem.step_value;
            }
        } else {
            if (animationElem.textureRect.left <= 0) {
                animationElem.isAnimatedToRight = true;
                animationElem.haveLoopedOnce = true;
            } else {
                animationElem.textureRect.left -= animationElem.step_value;
            }
        }

        animationElem.last_animation_step_time = currentTime;
    }
};

/**
 * @brief Get the flash animation entity related to the given entity ID.
 *
 * @param flashEntityId ID of the entity with the flash animation.
 * @return int The related entity ID, or -1 if not found.
 */
int AnimationSystem::getRelatedEntityFlash(int flashEntityId) {
    for (size_t i = 0, size = relatedIdFlashAnimations.size(); i < size; i++) {
        if (flashEntityId == relatedIdFlashAnimations[i].first) {
            return relatedIdFlashAnimations[i].second;
        }
    }
    return -1;
}

/**
 * @brief Get all flash animation IDs related to the specified entity ID.
 *
 * @param entityId ID of the entity to get related flash animations for.
 * @return std::vector<int> Vector of related flash animation entity IDs.
 */
std::vector<int> AnimationSystem::getAllFlashByEntity(int entityId) {
    std::vector<int> entityFlashs;

    for (size_t i = 0, size = relatedIdFlashAnimations.size(); i < size; i++) {
        if (entityId == relatedIdFlashAnimations[i].second) {
            entityFlashs.push_back(relatedIdFlashAnimations[i].first);
        }
    }
    return entityFlashs;
}

/**
 * @brief Add a relationship between a flash animation entity and the entity it is related to.
 *
 * @param relatedEntityId ID of the entity that the flash animation is related to.
 * @param flashEntityId ID of the flash animation entity.
 */
void AnimationSystem::addRelatedEntityFlash(int relatedEntityId, int flashEntityId) {
    std::pair<int, int> pair = std::make_pair(flashEntityId, relatedEntityId);

    relatedIdFlashAnimations.push_back(pair);
}

/**
 * @brief Remove the relationship for the specified flash animation entity ID.
 *
 * @param flashEntityId ID of the flash animation entity to remove the relationship for.
 */
void AnimationSystem::removeRelatedEntityFlash(int flashEntityId) {
    for (auto it = relatedIdFlashAnimations.begin(); it != relatedIdFlashAnimations.end(); ++it) {
        if (flashEntityId == it->first) {
            relatedIdFlashAnimations.erase(it);
            break;
        }
    }
}

/**
 * @brief Check if an entity already has a flash animation of a certain type.
 *
 * @param relatedEntityId ID of the entity to check for flash animations.
 * @param flashAnimType The type of flash animation to check for.
 * @param em Reference to the EntityManager to query existing entities.
 * @return true If there is already a flash animation of the specified type for the entity.
 * @return false If there is no flash animation of the specified type for the entity.
 */
bool AnimationSystem::doEntityAlreadyHaveFlash(int relatedEntityId, std::string flashAnimType, EntityManager& em) {
    std::vector<int> flashIds = getAllFlashByEntity(relatedEntityId);

    for (size_t i = 0, size = flashIds.size(); i < size; i++) {
        if (em.getEntityType(flashIds[i]) == flashAnimType) {
            return true;
        }
    }
    return false;
}
