cmake_minimum_required(VERSION 3.5)

if(MSVC)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
  add_compile_options(/W3)
elseif(UNIX)
  set(CMAKE_TOOLCHAIN_FILE "./external/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(R-Type)

add_definitions(-D_WIN32_WINNT=0x0601)
set(CMAKE_CXX_STANDARD 20)

find_package(asio CONFIG REQUIRED)
set(SFML_DIR "external/vcpkg/installed/x64-windows/share/sfml")
find_package(SFML COMPONENTS graphics window audio system CONFIG REQUIRED)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(libs)
