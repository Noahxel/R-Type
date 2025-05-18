# R-Type Project 🛸

## Welcome to R-Type

Welcome to R-Type, a classic reborn in modern C++.

This project is a tribute to the iconic arcade game, reimagined using contemporary programming techniques and technologies. Experience the thrill of piloting your spacecraft through challenging levels, dodging enemies.

## Language and Tools 🛠️

![C++](https://img.shields.io/badge/-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=sfml&logoColor=white)
![ASIO](https://img.shields.io/badge/-ASIO-238636?style=for-the-badge)
![CMake](https://img.shields.io/badge/-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![vcpkg](https://img.shields.io/badge/-vcpkg-F7DF1E?style=for-the-badge)

### Platform Support 💻

![Linux](https://img.shields.io/badge/-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![macOS](https://img.shields.io/badge/-macOS-000000?style=for-the-badge&logo=apple&logoColor=white)
![Windows](https://img.shields.io/badge/-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)


- **Language:** C++
- **Networking:** Asio for asynchronous network programming
- **Dependencies Management:** [VCPKG](https://github.com/microsoft/vcpkg) to handle dependencies
- **Dependencies:** [SFML](https://github.com/SFML/SFML) / [ASIO](https://github.com/chriskohlhoff/asio)
- **Compilation:** Via [CMake](https://cmake.org/), use the scripts in `scripts` folder for your dedicated plateform (`Windows`, `MacOS`, `Linux`)
- **Binary Names:** `r-type_server`, `r-type_client`

## Project Overview 🔎

R-Type is a networked, multiplayer game that combines intense spaceship dodging with cooperative gameplay.

The project is split into three major part: ``SERVER`` / ``CLIENT`` / ``ECS``
![Screenshot_2024-07-02_13-45-22](https://github.com/EpitechPromo2026/B-CPP-500-PAR-5-2-rtype-hugo.pattein/assets/72030363/bbb2359b-5472-49ea-8cf1-af8bd2996e0c)


For complete documentation please go to [GitBook documentation](https://r-type-5.gitbook.io/r-type/).

### Server Features

- **Multiplayer Management:** Seamlessly handle multiple players and game sessions.
- **Asynchronous Processing:** Utilize Asio for efficient network communication without blocking operations.
- **Data Persistence:** Store and retrieve game data effectively, ensuring a consistent gaming experience.

### Client Features

- **Interactive Gameplay:** Engage in a fast-paced space battle, controlling your ship with real-time responsiveness.
- **Graphical Interface:** Experience the game with a modern and visually appealing client interface.
- **Custom Controls:** Tailor the gameplay experience with configurable controls and settings.

## Data Management

- **Efficient Networking:** Implement custom protocols for optimized data transmission between client and server.
- **Security:** Ensure secure data handling and protect against potential vulnerabilities in network communication.

## Installation and Usage 💾

For complete guidelines on setting up, building, and running the R-Type project, please refer to our comprehensive [GitBook documentation](https://r-type-5.gitbook.io/r-type/).

### Quick Start

#### Set Up Environment:

- Follow the detailed setup instructions in our GitBook to prepare your environment for building the project.

#### Build the Project:

- Instructions for compiling the server and client components are available in the GitBook.

#### Run and Play:

- Find step-by-step instructions on how to start the server and connect clients in the GitBook.

The GitBook provides detailed information on gameplay mechanics, controls, and features to enhance your R-Type experience.
