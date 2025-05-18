#pragma once
#include <asio.hpp>
#include <thread>
#include "../game/Server.hpp"

/**
 * @class MainServer
 * @brief Represents the main server responsible for initializing and running the game server.
 *
 * This class is responsible for setting up and starting the main game server using ASIO.
 * It encapsulates the necessary components and logic to get the server running.
 */
class MainServer {
   public:
    /**
     * @brief Starts the server.
     *
     * Initializes the necessary components for the server and starts it. This function handles
     * the server's network communications and runs the server in a separate thread.
     *
     * @return int Returns an integer indicating the success or failure of the server startup.
     *             SUCCESS (0) is returned if the server starts and runs correctly,
     *             while a non-zero value indicates an error.
     */
    int start(int maxPlayers) noexcept;
};
