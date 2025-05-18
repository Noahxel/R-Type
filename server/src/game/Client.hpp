#pragma once
#include <asio.hpp>
#include <deque>
#include <mutex>
#include <string>
#include "../../libs/ecs/Message.hpp"

/**
 * @class Client
 * @brief Handles client-side network communication using ASIO.
 *
 * This class encapsulates the functionality necessary for a client to communicate
 * with a server, including sending messages, receiving messages, and handling network
 * connections and disconnections.
 */
class Client {
   public:
    /**
     * @brief Constructs a new Client object.
     *
     * Initializes the client with the given ASIO IO context and a unique client identifier.
     * 
     * @param io_context ASIO IO context for asynchronous operations.
     * @param clientId The unique identifier for this client.
     */
    Client(asio::io_context& io_context, int clientId);

    /**
     * @brief Destructor for Client.
     * 
     * Ensures proper disconnection and cleanup of network resources.
     */
    ~Client();

    /**
     * @brief Sends a message to the server.
     *
     * Serializes the message and queues it for sending to the server.
     * 
     * @param msg The message to be sent.
     */
    void send(const Message& msg);

    /**
     * @brief Starts asynchronous reading from the server.
     *
     * Initiates the process to continuously read messages from the server.
     */
    void startRead();

    /**
     * @brief Disconnects the client from the server.
     *
     * Closes the socket and cancels all ongoing asynchronous operations.
     */
    void disconnect();

    /**
     * @brief Checks if there are any messages received from the server that have not been processed.
     * 
     * @return true if there are unprocessed messages, false otherwise.
     */
    bool hasReceivedMessages() const;

    /**
     * @brief Retrieves the next received message.
     *
     * If there are any messages in the queue, returns the next one and removes it from the queue.
     * 
     * @return Message The next message, or an empty message if the queue is empty.
     */
    Message getNextMessage();

    /**
     * @brief Gets the client's unique identifier.
     * 
     * @return int The client's ID.
     */
    int getId() const;

    /**
     * @brief Gets a reference to the client's socket.
     * 
     * @return asio::ip::tcp::socket& Reference to the socket used for network communication.
     */
    asio::ip::tcp::socket& getSocket();

   private:
    int id;                                    ///< Unique identifier for the client.
    asio::ip::tcp::socket socket;              ///< Socket for network communication.
    std::deque<std::string> outgoingMessages;  ///< Queue of messages to be sent to the server.
    Message received_message;                  ///< A single message received from the server (for immediate processing).
    std::deque<Message> received_messages;     ///< Queue of received messages.
    std::vector<char> receiveBuffer;           ///< Buffer for receiving data.
    asio::steady_timer timer;                  ///< Timer for handling periodic tasks.
    std::mutex socket_mutex;                   ///< Mutex for socket operations to ensure thread safety.

    /**
     * @brief Writes all queued messages to the server.
     *
     * This method sends messages from the outgoing queue to the server using asynchronous operations.
     */
    void writeMessages();
};
