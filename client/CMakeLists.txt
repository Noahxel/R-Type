set(CLIENT_SOURCES
    src/Client.cpp
    src/main.cpp
)

find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)

file(GLOB_RECURSE CLIENT_SOURCES "src/*.cpp")
add_executable(r-type_client ${CLIENT_SOURCES})

target_include_directories(r-type_client
    PRIVATE
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/libs  # Add the path to ecs-libs headers
)

target_link_libraries(r-type_client
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    ecs-libs  # Add ecs-libs here
)
