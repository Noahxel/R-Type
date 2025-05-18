#include "MainServer.hpp"
#include "CommonDefs.hpp"
#include "ErrorHandler.hpp"

/**
 * @brief Starts the main server.
 *
 * This method initializes and starts the server using ASIO for handling network
 * communications. It runs the server on a separate thread and handles any exceptions
 * that occur during the server's execution.
 *
 * @return int Returns SUCCESS (0) if the server runs and stops without errors,
 *             and a non-zero error code if an exception occurs.
 */
int MainServer::start(int maxPlayers) noexcept {
    try {
        asio::io_context io_context;
        Server server(io_context, GameUtilities::SERVER_PORT, maxPlayers);
        std::thread serverThread([&io_context]() { io_context.run(); });
        server.run();
        serverThread.join();
    } catch (std::exception& e) {
        ErrorHandler::handle(e);
    }
    return SUCCESS;
}
