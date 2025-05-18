#include "ConnectionManager.hpp"

/**
 * @brief Constructs a new Connection Manager object.
 *
 * Initializes the acceptor to listen for incoming connections on the specified port.
 * It also outputs the server's IP and port information to the console.
 *
 * @param io_context ASIO IO context for asynchronous operations.
 * @param port The port number on which the server will listen for incoming connections.
 */
ConnectionManager::ConnectionManager(asio::io_context& io_context, short port, int maxPlayers)
    : io_context_(io_context),
      acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::address::from_string(IPResolver::getActualIP(io_context_)), port)),
      maxPlayers_(maxPlayers) {
    std::string actual_ip = IPResolver::getActualIP(io_context_);
    std::cout << "Server starting on IP: " << actual_ip << " Port: " << port << std::endl;
    std::cout << "To join the game, use: ./r-type_client " << actual_ip << std::endl;
}

/**
 * @brief Starts accepting client connections asynchronously.
 *
 * Waits for incoming client connections and sets up each new client. If the maximum
 * number of players is reached, it stops accepting new connections and triggers the game
 * start callback.
 *
 * @param gameStartCallback Callback function to be called when the maximum number of players is reached.
 */
void ConnectionManager::acceptConnections(std::function<void()> gameStartCallback) {
    std::cout << "Waiting for client connections..." << std::endl;
    if (clients_.size() < this->maxPlayers_) {
        int newClientId = clients_.size() + 1;
        auto client = std::make_shared<Client>(io_context_, newClientId);
        acceptor_.async_accept(client->getSocket(), [this, client, gameStartCallback](std::error_code ec) {
            if (!ec) {
                std::cout << "New client connected with ID: " << client->getId() << std::endl;
                clients_.push_back(client);
                client->startRead();
                if (clients_.size() < this->maxPlayers_) {
                    acceptConnections(gameStartCallback);
                } else {
                    gameStartCallback();
                }
            } else {
                std::cerr << "Error accepting client: " << ec.message() << std::endl;
            }
        });
    } else {
        std::cout << "Maximum number of players reached. No longer accepting new connections." << std::endl;
    }
}

/**
 * @brief Gets a reference to the list of connected clients.
 *
 * @return std::vector<std::shared_ptr<Client>>& Reference to the vector of connected clients.
 */
std::vector<std::shared_ptr<Client>>& ConnectionManager::getClients() {
    return clients_;
}

/**
 * @brief Gets a reference to the ASIO IO context.
 *
 * @return asio::io_context& Reference to the ASIO IO context used for network operations.
 */
asio::io_context& ConnectionManager::getIoContext() {
    return io_context_;
}
