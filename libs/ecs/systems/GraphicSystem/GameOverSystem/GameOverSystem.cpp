#include "GameOverSystem.hpp"

/**
 * @brief Constructs the GameOverSystem and loads the necessary font for the game over text.
 *
 * The constructor attempts to load a specific font from the assets directory. If the font
 * loading fails, it outputs an error message to the standard error.
 */
GameOverSystem::GameOverSystem() {
    if (!gameOverFont.loadFromFile("assets/sixty.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    gameOverText.setFont(gameOverFont);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);

}

/**
 * @brief Displays the game over text on the window.
 *
 * Clears the window, sets the position of the game over text to the center, and then
 * draws the text on the window. Finally, it displays the updated window.
 *
 * @param w Pointer to the SFML RenderWindow where the game over text will be displayed.
 */
void GameOverSystem::gameOverDisplay(sf::RenderWindow* w) {
    w->clear(sf::Color::Black);
    gameOverText.setPosition(static_cast<float>(w->getSize().x) / 2.0f, static_cast<float>(w->getSize().y) / 2.0f);
    w->draw(gameOverText);
    w->display();
}
