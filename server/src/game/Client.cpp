#include "Client.hpp"
#include <asio/write.hpp>
#include <iostream>

/**
 * @brief Constructs a new Client object.
 * 
 * @param io_context ASIO IO context for asynchronous operations.
 * @param clientId The unique identifier for this client.
 */
Client::Client(asio::io_context& io_context, int clientId)
    : id(clientId), socket(io_context), outgoingMessages(), received_message(), timer(io_context) {
    receiveBuffer.resize(1024);
}

/**
 * @brief Destructor for Client, ensuring disconnection and cleanup.
 */
Client::~Client() {}

/**
 * @brief Sends a message to the server.
 *
 * Serializes and queues a message for sending. It triggers the write operation
 * if there are no ongoing write operations.
 * 
 * @param msg The message to send.
 */
void Client::send(const Message& msg) {
    std::string serializedMessage = msg.serialize();
    bool isWriting = !outgoingMessages.empty();
    outgoingMessages.push_back(serializedMessage);
    if (!isWriting) {
        writeMessages();
    }
}

/**
 * @brief Starts an asynchronous read operation to receive messages from the server.
 */
void Client::startRead() {
    std::lock_guard<std::mutex> lock(socket_mutex);
    if (!socket.is_open())
        return;  // Prevent reading from a closed socket

    socket.async_read_some(asio::buffer(receiveBuffer), [this](std::error_code ec, std::size_t length) {
        if (!ec) {
            std::string receivedData(receiveBuffer.begin(), receiveBuffer.begin() + length);
            Message receivedMessage = Message::deserialize(receivedData);
            received_messages.push_back(receivedMessage);
            startRead();
        } else if (ec != asio::error::operation_aborted) {
            // Handle the error accordingly
            std::cerr << "Read failed: " << ec.message() << std::endl;
        }
    });
}

/**
 * @brief Disconnects the client from the server.
 * 
 * Closes the socket and cancels all pending asynchronous operations.
 */
void Client::disconnect() {
    asio::error_code ec;
    socket.cancel(ec);  // Cancel all asynchronous operations
    if (ec) {
        std::cerr << "Cancel failed: " << ec.message() << std::endl;
    }

    if (socket.is_open()) {
        socket.close(ec);  // Close the socket
        if (ec) {
            std::cerr << "Close failed: " << ec.message() << std::endl;
        }
    }

    timer.cancel(ec);  // Cancel the timer
    if (ec) {
        std::cerr << "Timer cancel failed: " << ec.message() << std::endl;
    }
}

/**
 * @brief Writes all messages in the outgoing queue to the server.
 * 
 * Uses asynchronous write operations to send the messages.
 */
void Client::writeMessages() {
    std::lock_guard<std::mutex> lock(socket_mutex);
    if (outgoingMessages.empty() || !socket.is_open())
        return;

    auto& serializedMsg = outgoingMessages.front();
    asio::async_write(socket, asio::buffer(serializedMsg), [this](std::error_code ec, std::size_t /* length */) {
        if (!ec) {
            outgoingMessages.pop_front();
            if (!outgoingMessages.empty()) {
                writeMessages();
            }
        } else {
            std::cerr << "Write failed: " << ec.message() << std::endl;
            socket.close();
        }
    });
}

/**
 * @brief Checks if there are received messages pending processing.
 * 
 * @return true if there are messages, false otherwise.
 */
bool Client::hasReceivedMessages() const {
    if (received_messages.size() == 0) {
        return false;
    }

    return !received_messages.empty();
}

/**
 * @brief Retrieves the next message from the received messages queue.
 * 
 * @return Message The next message if available, or an empty message if not.
 */
Message Client::getNextMessage() {
    if (!received_messages.empty()) {
        Message msg = received_messages.front();
        received_messages.pop_front();
        return msg;
    }
    return Message();
}

/**
 * @brief Gets the client's unique identifier.
 * 
 * @return int The client's ID.
 */
int Client::getId() const {
    return id;
}

/**
 * @brief Gets a reference to the client's socket.
 * 
 * @return asio::ip::tcp::socket& Reference to the socket.
 */
asio::ip::tcp::socket& Client::getSocket() {
    return socket;
}
