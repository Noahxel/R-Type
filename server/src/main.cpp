/**
 * @file main.cpp
 * @brief Entry point for the server application.
 *
 * This file contains the main function, which is the starting point for the server.
 * It initializes the MainServer object and starts the server. If the application
 * receives any command-line arguments, it displays help information.
 */

#include "CommonDefs.hpp"
#include "core/MainServer.hpp"
#include "utilities/HelpUtilities.hpp"

/**
 * @brief The main function, entry point for the server application.
 *
 * @param ac Argument count.
 * @param av Argument vector.
 * @return int The exit status of the application. Returns 0 on successful execution,
 *         non-zero otherwise.
 */
int main(int ac, char** av) {
    if (ac != 2) {
        return ServerUtilities::help(84);
    }

    int maxPlayers = std::stoi(av[1]);
    if (maxPlayers < 1 || maxPlayers > 4) {
        std::cerr << "Error: max_players must be between 1 and 4." << std::endl;
        return ServerUtilities::help(84);
    }

    MainServer server;
    return server.start(maxPlayers);
}