#include <iostream>
#include "GameClient.hpp"

const int SERVER_PORT = 4242;

/**
 * @brief The entry point for the game client.
 *
 * @param argc The count of command-line arguments.
 * @param argv The command-line arguments, expected to include the server's IP address.
 * @return int The exit status of the application.
 */
int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cout << "Usage: " << argv[0] << " <server_ip>" << std::endl;
            return 0;
        }

        asio::io_context io_context;
        GameClient client(io_context, argv[1], std::to_string(SERVER_PORT));

        std::thread clientThread([&io_context]() { io_context.run(); });

        client.run();

        clientThread.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
