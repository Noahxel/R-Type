#pragma once

#include "../../../Graphic/GraphicComponents.hpp"

/**
 * @class EventSystem
 * @brief System to handle and process user input events within the game.
 *
 * This class provides functionality to poll for and interpret events from the game window,
 * translating them into a format that can be understood and utilized by the game logic.
 */
class EventSystem {
   public:
    /**
     * @brief Polls for events from the given SFML RenderWindow and translates them into game commands.
     * 
     * This method checks for various SFML window events such as closure and key presses, and converts them into
     * a standard string format representing different game actions or commands.
     * 
     * @param w Reference to the SFML RenderWindow from which events are polled.
     * @return std::vector<std::string> A vector containing string representations of the polled events.
     */
    std::vector<std::string> getEvents(sf::RenderWindow& w);
};
