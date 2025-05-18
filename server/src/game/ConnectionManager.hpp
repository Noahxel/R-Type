#pragma once
#include <asio.hpp>
#include <functional>
#include <iostream>
#include <vector>
#include "../game/Client.hpp"
#include "../utilities/GameUtilities.hpp"
#include "../utilities/IPResolver.hpp"

/**
 * @class ConnectionManager
 * @brief Manages network connections for the server.
 *
 * This class is responsible for setting up the server to accept connections,
 * managing active client connections, and handling network communication.
 */
class ConnectionManager {
   public:
    /**
     * @brief Constructs a new Connection Manager object.
     *
     * Initializes the network acceptor to start listening for incoming client connections
     * on the specified port. It also outputs the server's IP and port information.
     *
     * @param io_context ASIO IO context for asynchronous operations.
     * @param port The port number on which the server will listen for incoming connections.
     */
    ConnectionManager(asio::io_context& io_context, short port, int maxPlayers);

    /**
     * @brief Starts accepting client connections asynchronously.
     *
     * Waits for incoming client connections and sets up each new client. When the maximum
     * number of players is reached, it triggers a callback to start the game.
     *
     * @param gameStartCallback Callback function to be called when the maximum number of players is reached.
     */
    void acceptConnections(std::function<void()> gameStartCallback);

    /**
     * @brief Gets a reference to the list of connected clients.
     *
     * @return std::vector<std::shared_ptr<Client>>& Reference to the vector of connected clients.
     */
    std::vector<std::shared_ptr<Client>>& getClients();

    /**
     * @brief Gets a reference to the ASIO IO context.
     *
     * @return asio::io_context& Reference to the ASIO IO context used for network operations.
     */
    asio::io_context& getIoContext();

   private:
    asio::io_context& io_context_;                  ///< Reference to the ASIO IO context.
    asio::ip::tcp::acceptor acceptor_;              ///< Acceptor used for listening for incoming connections.
    std::vector<std::shared_ptr<Client>> clients_;  ///< Vector holding the connected clients.
    int maxPlayers_;
};
