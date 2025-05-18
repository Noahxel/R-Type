#pragma once

#include <random>
#include <string>

/**
 * @namespace GameUtilities
 * @brief Namespace for defining various game constants and utilities.
 *
 * This namespace includes constants for server configuration, game dimensions, player and enemy
 * characteristics, and other utilities used throughout the game.
 */
namespace GameUtilities {

const int SERVER_PORT = 4242;             ///< The port number for the server.
const int SCREEN_WIDTH = 1920;            ///< The width of the game screen.
const int SCREEN_HEIGHT = 1000;           ///< The height of the game screen.
const int MAX_ENEMIES = 5;                ///< The maximum number of enemies allowed on screen.
const float ENEMY_SPEED = 300.0f;         ///< The speed of enemy entities.
const float ENEMY_WIDTH = 50.0f;          ///< The width of enemy entities.
const float ENEMY_HEIGHT = 50.0f;         ///< The height of enemy entities.
const float PLAYER_WIDTH = 40.0f;         ///< The width of player entities.
const float PLAYER_HEIGHT = 30.0f;        ///< The height of player entities.
const float OFF_SCREEN_X = -ENEMY_WIDTH;  ///< X-coordinate value representing an off-screen position to the left.
}  // namespace GameUtilities
