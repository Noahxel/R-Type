set(LIB_NAME ecs-libs)

set(LIBS_SOURCES
    ecs/systems/GraphicSystem/GraphicSystem.cpp
    ecs/systems/GraphicSystem/AnimationSystem/AnimationSystem.cpp
    ecs/systems/GraphicSystem/GameOverSystem/GameOverSystem.cpp
    ecs/systems/GraphicSystem/SpriteSystem/SpriteSystem.cpp
    ecs/systems/GraphicSystem/EntityManager/EntityManager.cpp
    ecs/systems/GraphicSystem/TextureLoader/TextureLoader.cpp
    ecs/systems/GraphicSystem/EventSystem/EventSystem.cpp

)

set(LIBS_HEADERS
    ecs/Graphic/Utils.hpp
    ecs/Graphic/UniqueEntity.hpp
    ecs/Graphic/SparseArray.hpp
    ecs/Graphic/ComponentManager.hpp
    ecs/Graphic/GraphicComponents.hpp
    ecs/systems/GraphicSystem/GraphicSystem.cpp
    ecs/systems/GraphicSystem/AnimationSystem/AnimationSystem.hpp
    ecs/systems/GraphicSystem/GameOverSystem/GameOverSystem.hpp
    ecs/systems/GraphicSystem/SpriteSystem/SpriteSystem.hpp
    ecs/systems/GraphicSystem/EntityManager/EntityManager.hpp
    ecs/systems/GraphicSystem/TextureLoader/TextureLoader.hpp
    ecs/systems/GraphicSystem/EventSystem/EventSystem.hpp
)

add_library(${LIB_NAME} ${LIBS_SOURCES} ${LIBS_HEADERS})

target_include_directories(${LIB_NAME} PUBLIC ecs)

target_link_libraries(${LIB_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
