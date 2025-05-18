#include "EventSystem.hpp"

/**
 * @brief Polls for events from the window and translates them into game commands.
 *
 * This function checks for window events such as closure and key presses and converts
 * them into a string representation of game commands.
 *
 * @param w Reference to the SFML RenderWindow object.
 * @return std::vector<std::string> A vector of strings representing game commands.
 */
std::vector<std::string> EventSystem::getEvents(sf::RenderWindow& w) {
    sf::Event event;
    std::vector<std::string> events;

    while (w.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            w.close();
            events.push_back("EXIT");
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                events.push_back("UP");
            else if (event.key.code == sf::Keyboard::Down)
                events.push_back("DOWN");
            else if (event.key.code == sf::Keyboard::Left)
                events.push_back("LEFT");
            else if (event.key.code == sf::Keyboard::Right)
                events.push_back("RIGHT");
        }
    }

    return (events);
}
