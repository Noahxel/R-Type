#pragma once

#include "../../../Graphic/GraphicComponents.hpp"

/**
 * @class GameOverSystem
 * @brief Manages the display of the game over screen.
 *
 * This class is responsible for setting up and displaying the game over text
 * when the game has ended. It manages the font and the text to be displayed on the game window.
 */
class GameOverSystem {
   public:
    /**
     * @brief Constructs the GameOverSystem object.
     * 
     * Initializes the game over font and text, setting up their properties such as size, color, and content.
     */
    GameOverSystem();

    /**
     * @brief Displays the game over text on the specified window.
     * 
     * Clears the window, positions the game over text at the center, and then draws the text.
     * 
     * @param w Pointer to the SFML RenderWindow where the game over text is displayed.
     */
    void gameOverDisplay(sf::RenderWindow* w);

    sf::Font gameOverFont;  ///< The font used for displaying the game over text.
    sf::Text gameOverText;  ///< The text object for the game over message.
};
