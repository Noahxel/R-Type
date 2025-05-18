@echo off

:: Run CMake configuration and build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="external\vcpkg\scripts\buildsystems\vcpkg.cmake" -DSFML_DIR="external\vcpkg\installed\x64-windows\share\sfml"

:: Build the project
cmake --build build

:: Check if the build was successful
IF %ERRORLEVEL% EQU 0 (
    move build\server\Debug\r-type_server.exe .
    move build\client\Debug\r-type_client.exe .
    echo Build completed successfully.
) ELSE (
    echo Build failed.
)
