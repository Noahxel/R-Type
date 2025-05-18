#pragma once

#include <sstream>
#include <string>
#include <vector>

/**
 * @enum RFC
 * @brief Enumerates the types of messages that can be sent and received in the game.
 *
 * This enumeration represents different types of messages that can be used
 * for communication between the client and server in the game, such as state updates,
 * input handling, and game control messages.
 */
enum class RFC {
    STATE_UPDATE = 200,  ///< Message for state updates.
    INPUT = 210,         ///< Message for input events.
    NEW_ENTITY = 220,    ///< Message indicating a new entity has been created.
    ENTITY_DEAD = 230,   ///< Message indicating an entity has been destroyed.
    GAME_OVER = 400      ///< Message indicating the game is over.
};

/**
 * @struct Message
 * @brief Represents a network message with a type and content.
 *
 * This structure is used to serialize and deserialize messages that are sent
 * and received over the network. It contains the message type and content.
 */
struct Message {
    RFC type;             ///< The type of the message, defined by the RFC enum.
    std::string content;  ///< The content of the message in string form.

    /**
     * @brief Serializes the message into a string format for sending over the network.
     *
     * @return A string representing the serialized message.
     */
    std::string serialize() const {
        std::ostringstream oss;
        oss << static_cast<int>(type) << " " << content;
        return oss.str();
    }

    /**
     * @brief Deserializes a string to create a Message object.
     *
     * @param data The string containing the serialized message data.
     * @return A Message object representing the deserialized data.
     */
    static Message deserialize(const std::string& data) {
        std::istringstream iss(data);
        Message message;
        int messageType;
        iss >> messageType;
        message.type = static_cast<RFC>(messageType);
        iss.ignore();
        std::getline(iss, message.content);
        return message;
    }
};
