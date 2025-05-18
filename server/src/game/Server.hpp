#pragma once
#include <asio.hpp>
#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <set>
#include <thread>
#include <vector>
#include "../utilities/RandomUtilities.hpp"
#include "CollisionSystem.hpp"
#include "ConnectionManager.hpp"
#include "EnemyMovementSystem.hpp"
#include "Message.hpp"
#include "Registry.hpp"

/**
 * @class Server
 * @brief Main class for handling server logic in the game.
 *
 * This class encapsulates all the server-side logic, including network communication,
 * game state management, and interaction between different game systems.
 */
class Server {
   public:
    /**
     * @brief Constructs a new Server object.
     *
     * Sets up the connection manager for network communication and initializes game systems.
     *
     * @param io_context ASIO IO context for asynchronous operations.
     * @param port The port number on which the server will listen for incoming connections.
     */
    Server(asio::io_context& io_context, short port, int maxPlayers)
        : connectionManager_(io_context, port, maxPlayers), maxPlayers_(maxPlayers), enemySpawnTimer(connectionManager_.getIoContext()) {
        connectionManager_.acceptConnections([this]() { this->startGame(); });
        enemyMovementSystem =
            std::make_shared<EnemyMovementSystem>(static_cast<float>(GameUtilities::SCREEN_WIDTH), GameUtilities::OFF_SCREEN_X,
                                                  GameUtilities::ENEMY_SPEED, GameUtilities::SCREEN_HEIGHT - GameUtilities::ENEMY_HEIGHT);
        registry.addSystem(enemyMovementSystem);
        collisionSystem = std::make_shared<CollisionSystem>([this](int playerId) { handlePlayerCollision(playerId); }, activeEnemies);
        registry.addSystem(collisionSystem);
    }

    /**
     * @brief Main run loop of the server.
     *
     * Handles the game loop, processing client inputs, updating game state, and sending updates to clients.
     */
    void run() {
        while (isRunning) {
            float deltaTime = registry.updateDeltaTime();

            if (gameStarted) {
                processClientInputs();
                updateGameState(deltaTime);
                sendUpdates();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }

    /**
     * @brief Processes client inputs and updates entities accordingly.
     */
    void processClientInputs() {
        const float moveStep = 10.0f;

        for (auto& client : connectionManager_.getClients()) {
            while (client && client->hasReceivedMessages()) {
                Message msg = client->getNextMessage();
                Entity playerEntity(client->getId());
                auto posComp = registry.getComponent<PositionComponent>(playerEntity);

                if (!posComp)
                    continue;

                if (msg.content == "UP" && (posComp->y - moveStep > 0)) {
                    posComp->y -= moveStep;
                } else if (msg.content == "DOWN" && (posComp->y + GameUtilities::PLAYER_HEIGHT + moveStep < GameUtilities::SCREEN_HEIGHT)) {
                    posComp->y += moveStep;
                } else if (msg.content == "LEFT" && (posComp->x - moveStep > 0)) {
                    posComp->x -= moveStep;
                } else if (msg.content == "RIGHT" && (posComp->x + GameUtilities::PLAYER_WIDTH + moveStep < GameUtilities::SCREEN_WIDTH)) {
                    posComp->x += moveStep;
                }
            }
        }
    }

    /**
     * @brief Creates a new enemy entity and adds it to the game.
     */
    void createEnemy() {
        if (gameStarted && activeEnemies.size() < GameUtilities::MAX_ENEMIES) {
            Entity enemyEntity = registry.createEntity();
            notifyNewEntityCreation("Enemy", enemyEntity.id());
            float randomY = RandomUtilities::getRandomY(GameUtilities::SCREEN_HEIGHT - GameUtilities::ENEMY_HEIGHT);
            std::cout << "Enemy entity created with ID: " << enemyEntity.id() << std::endl;
            registry.addComponent<PositionComponent>(enemyEntity, GameUtilities::SCREEN_WIDTH, randomY);
            registry.addComponent<HitboxComponent>(enemyEntity, GameUtilities::ENEMY_WIDTH, GameUtilities::ENEMY_HEIGHT);
            std::cout << "Enemy position and hitbox components added." << std::endl;
            activeEnemies.insert(enemyEntity.id());
            collisionSystem->updateEnemyEntityIds(activeEnemies);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    /**
     * @brief Schedules the spawning of enemy entities at random intervals.
     */
    void scheduleEnemySpawn() {
        enemySpawnTimer.expires_after(std::chrono::seconds(RandomUtilities::getRandomSpawnTime(2, 5)));
        enemySpawnTimer.async_wait([this](const std::error_code& ec) {
            if (!ec) {
                createEnemy();
                scheduleEnemySpawn();
            }
        });
    }

    /**
     * @brief Creates player entities for each connected client.
     */
    void createPlayers() {
        for (int i = 0; i < this->maxPlayers_; ++i) {
            Entity player = registry.createEntity();
            int playerId = connectionManager_.getClients()[i]->getId();
            notifyNewEntityCreation("Player", playerId);
            registry.addComponent<PositionComponent>(
                player, 0.0f, (GameUtilities::SCREEN_HEIGHT / maxPlayers_ * i) + (GameUtilities::SCREEN_HEIGHT / maxPlayers_) / 2);
            registry.addComponent<PlayerComponent>(player, playerId);
            registry.addComponent<HitboxComponent>(player, GameUtilities::PLAYER_WIDTH, GameUtilities::PLAYER_HEIGHT);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    /**
     * @brief Notifies all clients of a new entity's creation.
     *
     * @param entityType Type of the entity (e.g., "Player", "Enemy").
     * @param entityId Unique identifier of the new entity.
     */
    void notifyNewEntityCreation(const std::string& entityType, int entityId) {
        Message newEntityMsg;
        newEntityMsg.type = RFC::NEW_ENTITY;
        newEntityMsg.content = entityType + " " + std::to_string(entityId) + ';';
        std::cout << "NEW ENTITY ! SENDING : |" << newEntityMsg.content << "|" << std::endl;
        for (auto& client : connectionManager_.getClients()) {
            client->send(newEntityMsg);
        }
    }

    /**
     * @brief Notifies all clients of an entity's death.
     *
     * @param entityId Unique identifier of the dead entity.
     */
    void notifyEntityDeath(int entityId) {
        Message deathMessage;
        deathMessage.type = RFC::ENTITY_DEAD;
        deathMessage.content = std::to_string(entityId) + ';';
        std::cout << "SENDING DEATH MESSAGE : " << deathMessage.content << std::endl;
        for (auto& client : connectionManager_.getClients()) {
            client->send(deathMessage);
        }
    }

    /**
     * @brief Starts the game once all players are connected.
     */
    void startGame() {
        std::cout << "Starting game with " << this->maxPlayers_ << " players." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        createPlayers();
        scheduleEnemySpawn();
        createEnemy();
        gameStarted = true;
    }

    /**
     * @brief Updates the game state based on the elapsed time since the last update.
     *
     * @param deltaTime Time elapsed since the last update.
     */
    void updateGameState(float deltaTime) { registry.updateSystems(deltaTime); }

    /**
     * @brief Handles the collision of a player with another entity.
     *
     * @param entityId Unique identifier of the collided player.
     */
    void handlePlayerCollision(int entityId) {

        auto clientIt = std::find_if(connectionManager_.getClients().begin(), connectionManager_.getClients().end(),
                                     [entityId](const auto& client) { return client->getId() == entityId; });
        if (clientIt != connectionManager_.getClients().end()) {
            Message gameOverMessage;
            gameOverMessage.type = RFC::GAME_OVER;
            gameOverMessage.content = "Player " + std::to_string(entityId) + " dead." + ';';
            (*clientIt)->send(gameOverMessage);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            registry.removeEntity(entityId);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            (*clientIt)->disconnect();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            connectionManager_.getClients().erase(clientIt);
            asio::steady_timer removal_timer(connectionManager_.getIoContext());
            notifyEntityDeath(entityId);
        }
        if (connectionManager_.getClients().begin() == connectionManager_.getClients().end()) {
            isRunning = false;
        }
    }

    /**
     * @brief Sends state updates to all connected clients.
     */
    void sendUpdates() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& client : connectionManager_.getClients()) {
            Message update_message;
            update_message.type = RFC::STATE_UPDATE;

            for (const Entity& entity : registry.getEntities()) {
                auto posComp = registry.getComponent<PositionComponent>(entity);
                if (posComp) {
                    if (registry.getComponent<PlayerComponent>(entity)) {
                        update_message.content +=
                            std::to_string(entity.id()) + ' ' + std::to_string(posComp->x) + ' ' + std::to_string(posComp->y) + ',';
                    } else if (registry.getComponent<HitboxComponent>(entity) && !registry.getComponent<PlayerComponent>(entity)) {
                        update_message.content +=
                            std::to_string(entity.id()) + ' ' + std::to_string(posComp->x) + ' ' + std::to_string(posComp->y) + ',';
                    }
                }
            }
            update_message.content += ';';
            client->send(update_message);
        }
    }

   private:
    ConnectionManager connectionManager_;                      ///< Manages client connections.
    bool isRunning = true;                                     ///< Flag indicating if the server is running.
    bool gameStarted = false;                                  ///< Flag indicating if the game has started.
    Registry registry;                                         ///< Manages entities and components.
    std::mutex mutex_;                                         ///< Mutex for thread-safe operations.
    std::shared_ptr<EnemyMovementSystem> enemyMovementSystem;  ///< System for enemy movement logic.
    std::shared_ptr<CollisionSystem> collisionSystem;          ///< System for collision detection and handling.
    std::set<int> activeEnemies;                               ///< Set of active enemy entity IDs.
    asio::steady_timer enemySpawnTimer;                        ///< Timer for scheduling enemy spawns.
    int maxPlayers_;
};
