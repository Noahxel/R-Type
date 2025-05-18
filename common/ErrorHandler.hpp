/*
** EPITECH PROJECT, 2024
** ErrorHandler.hpp
** File description:
** error handler
*/

#include <exception>
#include <iostream>

namespace ErrorHandler {
static void handle(const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
}
}  // namespace ErrorHandler
