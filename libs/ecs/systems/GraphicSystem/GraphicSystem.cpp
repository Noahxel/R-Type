#include "GraphicSystem.hpp"

/**
 * @brief Constructs a GraphicSystem object and initializes its components.
 *
 * @param windowWidth Width of the game window.
 * @param windowHeight Height of the game window.
 */
GraphicSystem::GraphicSystem(int windowWidth, int windowHeight)
    : window(new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "RType")),
      textureLoader(),
      spriteSystem(),
      animationSystem(),
      eventSystem(),
      gameOverSystem(),
      isGameOver(false) {
    cm = ComponentManager();
    em = EntityManager();
    cm.registerComponent<SpriteComponent>();
    cm.registerComponent<AnimationComponent>();
    cm.registerComponent<PosComponent>();
    cm.registerComponent<ScaleComponent>();
}

/**
 * @brief Sets a new position for a specific entity in the game.
 *
 * @param x The x-coordinate of the new position.
 * @param y The y-coordinate of the new position.
 * @param entityId The ID of the entity whose position is being set.
 */
void GraphicSystem::setNewPos(float x, float y, int entityId) {
    SparseArray<PosComponent>& posArray = cm.getSparseArray<PosComponent>();
    Utils::Vec2 vecPos(x, y);
    int eId = em.getIndex(entityId);

    if (eId > -1) {
        if (posArray[eId]->coord == vecPos)
            return;
        if (em.getEntityType(entityId) == "Player") {
            if (posArray[eId]->coord.x < vecPos.x)
                factory(-1, "Fireship", entityId);
        }
        posArray[eId]->coord = vecPos;
    }
}

/**
 * @brief Refreshes the game by updating sprites, positions, animations, and scales of entities.
 */
void GraphicSystem::refreshGame() {
    SparseArray<SpriteComponent>& spritesArray = cm.getSparseArray<SpriteComponent>();
    SparseArray<PosComponent>& positionArray = cm.getSparseArray<PosComponent>();
    SparseArray<ScaleComponent>& scaleArray = cm.getSparseArray<ScaleComponent>();
    SparseArray<AnimationComponent>& animationArray = cm.getSparseArray<AnimationComponent>();

    for (size_t i = 0, size = em.serverEntitiesId.size(); i < size; i++) {
        if (spritesArray[i].has_value()) {
            int id = em.serverEntitiesId[i].first;
            bool isFlashAnimation = id < 0 ? true : false;

            if (animationArray[i].has_value()) {
                if (isFlashAnimation && animationArray[i]->haveLoopedOnce) {
                    removeEntity(id);
                    animationSystem.removeRelatedEntityFlash(id);
                    continue;
                }
                animationSystem.AnimateElem(animationArray[i].value());
                spriteSystem.setSpriteRect(spritesArray[i].value(), animationArray[i]->textureRect);
            }

            if (positionArray[i].has_value()) {
                if (isFlashAnimation) {
                    int relatedId = animationSystem.getRelatedEntityFlash(id);
                    Utils::Vec2 computedCoords = positionArray[relatedId]->coord;
                    if (!positionArray[relatedId].has_value()) {
                        computedCoords = positionArray[i]->coord;
                    } else {
                        if (em.getEntityType(id) == "Fireship") {
                            computedCoords.x -= 65;
                            computedCoords.y -= 15;
                        }
                    }
                    spriteSystem.setSpritePos(spritesArray[i].value(), computedCoords);
                } else {
                    spriteSystem.setSpritePos(spritesArray[i].value(), positionArray[i]->coord);
                }
            }

            if (scaleArray[i].has_value()) {
                spriteSystem.setSpriteScale(spritesArray[i].value(), scaleArray[i].value());
            }

            // std::cout << "drawing entity: " << i << std::endl;

            spriteSystem.draw(window, spritesArray[i].value());
        }
    }
}

/**
 * @brief Displays all elements in the game window, including handling the game over scenario.
 */
void GraphicSystem::displayAll() {
    if (isGameOver) {
        gameOverSystem.gameOverDisplay(window);
        return;
    }

    window->clear(sf::Color::Black);
    refreshGame();
    window->display();
}

/**
 * @brief Removes a specific entity from the game.
 *
 * @param entityId The ID of the entity to remove.
 */
void GraphicSystem::removeEntity(int entityId) {
    int index = em.getIndex(entityId);

    if (index == -1) {
        return;
    }

    SparseArray<SpriteComponent>& spritesArray = cm.getSparseArray<SpriteComponent>();
    SparseArray<PosComponent>& positionArray = cm.getSparseArray<PosComponent>();
    SparseArray<ScaleComponent>& scaleArray = cm.getSparseArray<ScaleComponent>();
    SparseArray<AnimationComponent>& animationArray = cm.getSparseArray<AnimationComponent>();

    spritesArray.removeComponent(index);
    positionArray.removeComponent(index);
    scaleArray.removeComponent(index);
    animationArray.removeComponent(index);
}

/**
 * @brief Factory method to create and initialize game entities.
 *
 * @param entityId The ID of the entity to create.
 * @param entityType The type of the entity (e.g., "Player", "Enemy").
 * @param relatedEntityPosId The ID of a related entity, used for positioning.
 */
void GraphicSystem::factory(int entityId, std::string entityType, int relatedEntityPosId) {
    if (relatedEntityPosId != -1) {
        if (animationSystem.doEntityAlreadyHaveFlash(relatedEntityPosId, entityType, em))
            return;
    }
    int animMaxStep = 0;
    int animStep = 0;
    int animSpeed = 0;
    Utils::Vec2 elemScale(1, 1);
    Utils::Vec2 defaultPos(-100, -100);
    sf::IntRect spriteRect(0, 0, 0, 0);
    SparseArray<SpriteComponent>& spritesArray = cm.getSparseArray<SpriteComponent>();
    SparseArray<PosComponent>& positionArray = cm.getSparseArray<PosComponent>();
    SparseArray<AnimationComponent>& animationArray = cm.getSparseArray<AnimationComponent>();
    SparseArray<ScaleComponent>& scaleArray = cm.getSparseArray<ScaleComponent>();

    em.addEntity(entityId, entityType);
    if (entityType == "Background") {
        animMaxStep = 3840;
        animStep = 1;
        animSpeed = 30;
        spriteRect = {0, 0, 1920, 1080};
        defaultPos = {0, 0};
    }
    if (entityType == "Player") {
        spriteRect = {0, 0, 78, 40};
        animStep = spriteRect.width;
        animMaxStep = 292;
        animSpeed = 150;
        entityType += std::to_string(em.addPlayerAndGetColor());
    }
    if (entityType == "Enemy") {
        spriteRect = {0, 0, 63, 69};
        animStep = spriteRect.width;
        animMaxStep = 434;
        animSpeed = 150;
    }
    if (entityType == "Fireship") {
        spriteRect = {0, 0, 69, 69};
        animStep = spriteRect.width;
        animMaxStep = 207;
        animSpeed = 100;
    }
    if (entityType == "Explosion") {
        spriteRect = {0, 0, 72, 72};
        animStep = spriteRect.width;
        animMaxStep = 360;
        animSpeed = 100;
    }

    if (relatedEntityPosId != -1) {
        animationSystem.addRelatedEntityFlash(relatedEntityPosId, em.getLowestId());
        defaultPos = positionArray[em.getIndex(relatedEntityPosId)]->coord;
    }

    AnimationComponent newAnim(animStep, animMaxStep, animSpeed);
    ScaleComponent newSize(elemScale);
    SpriteComponent newSprite;
    PosComponent newPos(defaultPos);

    sf::Texture* spriteText = textureLoader.getTextureByName(entityType);
    if (spriteText)
        spriteSystem.setSpriteProperties(newSprite, *spriteText);
    else
        std::cout << "no texture loaded for: " << entityType << std::endl;

    newAnim.textureRect = spriteRect;
    newAnim.isReverted = textureLoader.getRevertedByName(entityType);
    spritesArray.insertComponent(spritesArray.size(), std::move(newSprite));
    positionArray.insertComponent(positionArray.size(), std::move(newPos));
    animationArray.insertComponent(animationArray.size(), std::move(newAnim));
    scaleArray.insertComponent(scaleArray.size(), std::move(newSize));
    std::cout << entityType << " " << entityId << " created\n";
}
