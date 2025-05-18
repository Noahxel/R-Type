set(SERVER_SOURCES
    src/game/Client.cpp
    src/game/ConnectionManager.cpp
    src/core/MainServer.cpp
    src/main.cpp
)

add_executable(r-type_server ${SERVER_SOURCES})
target_include_directories(r-type_server PRIVATE ${CMAKE_SOURCE_DIR}/common ${CMAKE_SOURCE_DIR}/libs/ecs/)

target_link_libraries(r-type_server asio::asio)
