#pragma once
#include <iostream>

/**
 * @namespace ServerUtilities
 * @brief Namespace for utility functions related to the server.
 *
 * Contains helper functions that provide various utilities specific to the server application,
 * like displaying usage instructions.
 */
namespace ServerUtilities {

/**
     * @brief Displays the usage information for the server application.
     *
     * This function prints the usage instructions for running the server application.
     * It can be called when the server is started incorrectly or when help is requested.
     *
     * @param returnValue The return value to be propagated back through the function call.
     * @return int The return value provided as an argument (used for exiting the program with a specific status).
     */
static int help(const int returnValue) {
    std::cout << "USAGE:\n\t./r-type_server [max_players]\n"
              << "max_players: 1, 2, or 3 - Maximum number of players required for the game to start." << std::endl;
    return returnValue;
}
}  // namespace ServerUtilities
