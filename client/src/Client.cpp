/**
 * @file Client.cpp
 * @brief Implementation of the client functions.
 *
 * Contains the implementation of the client-side functions necessary for the application.
 */

#include <iostream>
#include <vector>

#include "CommonDefs.hpp"

static int help(const int returnValue) {
    std::cout << "USAGE:\n\t./r-type_client" << std::endl;
    return returnValue;
}

/**
 * @brief Starts and runs the client application.
 *
 * @param args Command line arguments provided to the client.
 * @return int Returns SUCCESS on successful execution, otherwise returns an error code.
 */
int client(const std::vector<std::string>& args) {
    if (args.size() > 1)
        return (args.size() == 2 && args[1] == "-h") || args[1] == "--help" ? help(SUCCESS) : help(84);
    return SUCCESS;
}
