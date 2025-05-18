#pragma once

#include <asio.hpp>
#include "../../libs/ecs/Message.hpp"
#include "../../libs/ecs/systems/GraphicSystem/GraphicSystem.hpp"

/**
 * @class GameClient
 * @brief Handles the client-side game logic and network communication.
 *
 * This class manages the connection to the server, processes incoming and outgoing messages,
 * and integrates the graphics system for rendering the game state.
 */
class GameClient {
   public:
    /**
     * @brief Constructs a new Game Client object and initiates a connection to the server.
     *
     * @param io_context ASIO IO context for asynchronous operations.
     * @param server The server's IP address or hostname.
     * @param port The server's port as a string.
     */
    GameClient(asio::io_context& io_context, const std::string& server, const std::string& port);

    /**
     * @brief Loads the texture assets required for the game.
     */
    void loadTextures();

    /**
     * @brief Runs the main loop of the client, handling input and rendering.
     */
    void run();

    /**
     * @brief Processes user input and sends relevant commands to the server.
     */
    void handleInput();

    /**
     * @brief Updates the game state based on the latest data received from the server.
     *
     * @param stateData The serialized state data as a string.
     */
    void updateGameState(const std::string& stateData);

    /**
     * @brief Establishes a connection to the server.
     *
     * @param server The server's IP address or hostname.
     * @param port The server's port as a string.
     */
    void connectToServer(const std::string& server, const std::string& port);

    /**
     * @brief Sends the player's input to the server for processing.
     *
     * @param input The player's input as a string.
     */
    void sendInput(const std::string& input);

    /**
     * @brief Starts an asynchronous read operation to receive updates from the server.
     */
    void startRead();

    /**
     * @brief Processes updates received from the server.
     *
     * @param message The message received from the server containing update information.
     */
    void receiveUpdates(const Message& message);

    /**
     * @brief Disconnects the client from the server and cleans up resources.
     */
    void disconnect();

   private:
    asio::io_context& io_context_;    ///< The ASIO IO context for handling asynchronous operations.
    asio::ip::tcp::socket socket_;    ///< The socket used for network communication with the server.
    std::vector<char> receiveBuffer;  ///< Buffer used for receiving data from the server.
    GraphicSystem gs;                 ///< The graphics system for rendering the game state.
};
