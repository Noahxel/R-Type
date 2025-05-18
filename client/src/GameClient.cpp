#include "GameClient.hpp"

/**
 * @brief Construct a new Game Client object.
 *
 * @param io_context ASIO IO context for asynchronous operations.
 * @param server The server's IP address or hostname.
 * @param port The server's port number as a string.
 */
GameClient::GameClient(asio::io_context& io_context, const std::string& server, const std::string& port)
    : io_context_(io_context), socket_(io_context), gs(int(1920), int(1080)) {
    loadTextures();
    connectToServer(server, port);
}

/**
 * @brief Loads all the necessary textures from the assets directory.
 */
void GameClient::loadTextures() {
    gs.textureLoader.addTexture("assets/background.png", "Background");
    gs.textureLoader.addTexture("assets/player_1_reverted.gif", "Player1");
    gs.textureLoader.addTexture("assets/player_2_reverted.gif", "Player2");
    gs.textureLoader.addTexture("assets/player_3_reverted.gif", "Player3");
    gs.textureLoader.addTexture("assets/player_4_reverted.gif", "Player4");
    gs.textureLoader.addTexture("assets/player_5_reverted.gif", "Player5");
    gs.textureLoader.addTexture("assets/fireship_reverted.gif", "Fireship");
    gs.textureLoader.addTexture("assets/explosion.gif", "Explosion");
    gs.textureLoader.addTexture("assets/enemy.png", "Enemy");
    sf::Font gameFont;
    sf::Text scoreText;
    sf::Text directionText;
    sf::Sprite playButton;
    sf::Sprite pauseButton;
    sf::Sprite volumeUp;
    sf::Sprite volumeMute;
    sf::Texture playTexture;
    sf::Texture pauseTexture;
    sf::Texture volumeUpTexture;
    sf::Texture volumeMuteTexture;
    sf::SoundBuffer alertBuffer;
    sf::Sound alertSound;
}

void loadAccessibilityAssets() {
        if (!gameFont.loadFromFile("assets/sixty.ttf")) {
            std::cerr << "Failed to load sixty.ttf" << std::endl;
        }

        scoreText.setFont(gameFont);
        scoreText.setCharacterSize(24);
        scoreText.setPosition(10.f, 10.f); // Top-left corner for score

        directionText.setFont(gameFont);
        directionText.setCharacterSize(24);
        directionText.setPosition(960.f, 1040.f); // Bottom-center for direction

        playTexture.loadFromFile("assets/play-button-arrowhead.png");
        pauseTexture.loadFromFile("assets/pause.png");
        volumeUpTexture.loadFromFile("assets/monter-le-son.png");
        volumeMuteTexture.loadFromFile("assets/volume-mute.png");

        playButton.setTexture(playTexture);
        pauseButton.setTexture(pauseTexture);
        volumeUp.setTexture(volumeUpTexture);
        volumeMute.setTexture(volumeMuteTexture);

        playButton.setPosition(1800.f, 10.f); // Position for play button
        pauseButton.setPosition(1800.f, 10.f); // Position for pause button
        volumeUp.setPosition(1740.f, 10.f); // Position for volume button
        volumeMute.setPosition(1740.f, 10.f); // Position for mute button

        alertBuffer.loadFromFile("assets/mise-en-garde.png");
        alertSound.setBuffer(alertBuffer);
    }


/**
 * @brief Main run loop for the game client. Handles input and display updates.
 */
void GameClient::run() {
    gs.factory(0, "Background");
    while (gs.window->isOpen()) {
        handleInput();
        gs.displayAll();
    }
}

/**
 * @brief Handles user input, translates it into game actions, and sends it to the server.
 */
void GameClient::handleInput() {
    std::vector<std::string> events = gs.eventSystem.getEvents(*gs.window);
    for (size_t i = 0, size = events.size(); i < size; i++) {
        if (events[i] == "EXIT") {
            std::exit(0);
        }
        sendInput(events[i]);
    }
}

/**
 * @brief Updates the game state based on the state data received from the server.
 *
 * @param stateData Serialized state data received from the server.
 */
void GameClient::updateGameState(const std::string& stateData) {
    std::set<int> activePlayerIds;
    std::set<int> activeEnemyIds;
    std::istringstream iss(stateData);
    std::string token;

    while (std::getline(iss, token, ',')) {
        std::istringstream tokenStream(token);
        float x, y;
        int entityId;

        tokenStream >> entityId >> x >> y;
        gs.setNewPos(x, y, entityId);
    }
}

void displayAccessibilityFeatures() {
        gs.window->draw(scoreText);
        gs.window->draw(directionText);
        gs.window->draw(volumeUp);
        gs.window->draw(playButton);
}

void updateAccessibilityFeatures() {
        scoreText.setString("Score: " + std::to_string(gs.getScore()));
        directionText.setString("Direction: " + gs.getCurrentDirection());

        // Example condition to play alert sound
        if (gs.enemyClose()) {
            alertSound.play();
        }
}

/**
 * @brief Initiates the connection to the game server.
 *
 * @param server The server's IP address or hostname.
 * @param port The server's port number as a string.
 */
void GameClient::connectToServer(const std::string& server, const std::string& port) {
    try {
        asio::ip::tcp::resolver resolver(io_context_);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(server, port);
        asio::async_connect(socket_, endpoints, [this](std::error_code ec, asio::ip::tcp::endpoint) {
            if (!ec) {
                std::cout << "Connected to the server!" << std::endl;
                startRead();
            } else {
                std::cerr << "Failed to connect: " << ec.message() << std::endl;
            }
        });
    } catch (std::exception& e) {
        std::cerr << "Exception in connectToServer: " << e.what() << std::endl;
    }
}

/**
 * @brief Sends a player's input to the server.
 *
 * @param input The player's input as a string.
 */
void GameClient::sendInput(const std::string& input) {
    Message message;
    message.type = RFC::INPUT;
    message.content = input;

    std::string serializedMessage = message.serialize();

    asio::async_write(socket_, asio::buffer(serializedMessage), [this](std::error_code ec, std::size_t /*length*/) {
        if (!ec) {
        } else {
            std::cerr << "Failed to send input: " << ec.message() << std::endl;
        }
    });
}

/**
 * @brief Starts the asynchronous read operation to receive data from the server.
 */
void GameClient::startRead() {
    receiveBuffer.resize(1024);

    socket_.async_read_some(asio::buffer(receiveBuffer), [this](std::error_code ec, std::size_t length) {
        if (!ec) {
            std::string receivedData(receiveBuffer.begin(), receiveBuffer.begin() + length);
            std::stringstream ss(receivedData);
            std::string token;

            while (std::getline(ss, token, ';')) {
                if (!token.empty()) {
                    Message receivedMessage = Message::deserialize(token);
                    receiveUpdates(receivedMessage);
                }
            }
            Message receivedMessage = Message::deserialize(receivedData);
            startRead();
        } else {
            std::cerr << "Failed to read: " << ec.message() << std::endl;
        }
    });
}

/**
 * @brief Processes updates received from the server.
 *
 * @param message The message received from the server.
 */
void GameClient::receiveUpdates(const Message& message) {
    if (message.type == RFC::STATE_UPDATE) {
        updateGameState(message.content);
    }
    if (message.type == RFC::GAME_OVER) {
        gs.isGameOver = true;
    }
    if (message.type == RFC::NEW_ENTITY) {
        std::istringstream iss(message.content);
        std::string entityType;
        int entityId;

        std::cout << "creating instruction: " << message.content << std::endl;
        iss >> entityType >> entityId;
        gs.factory(entityId, entityType);
    }
    if (message.type == RFC::ENTITY_DEAD) {
        gs.factory(-1, "Explosion", std::stoi(message.content));
        gs.removeEntity(std::stoi(message.content));
    }
}

/**
 * @brief Disconnects the client from the server, closing the socket.
 */
void GameClient::disconnect() {
    if (socket_.is_open()) {
        std::error_code ec;
        socket_.close(ec);
        if (ec) {
            std::cerr << "Failed to close socket: " << ec.message() << std::endl;
        }
    }
}
