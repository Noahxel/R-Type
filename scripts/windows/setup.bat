@echo off

:: Update git submodules
git submodule update --init --recursive

:: Install with vcpkg
echo Installing asio and SFML using vcpkg...
call .\external\vcpkg\bootstrap-vcpkg.bat
call .\external\vcpkg\vcpkg install asio:x64-windows sfml:x64-windows

:: Check for CMake installation
where cmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo CMake not found. Please install CMake manually or use an alternative method.
) else (
    echo CMake is already installed.
)

:: Additional installations (like Doxygen, pkg-config, and Clang) would typically require manual
:: installation or using a package manager like Chocolatey on Windows.

:: Starting build process
call .\scripts\windows\build.bat
