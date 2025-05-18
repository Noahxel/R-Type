#!/bin/sh

git submodule update --init --recursive

install_cmake() {
  echo "Checking for CMake..."
  if
    ! command -v cmake &
    >/dev/null
  then
    echo "CMake not found. Installing CMake..."
    if [ "$OS" = "Darwin" ]; then
      brew install cmake
    elif [ "$OS" = "Linux" ]; then
      if grep -q 'ID=ubuntu' /etc/os-release; then
        sudo apt-get install -y cmake
      elif grep -q 'ID=fedora' /etc/os-release; then
        sudo dnf install -y cmake
      fi
    fi
  else
    echo "CMake is already installed."
  fi
}

install_pkg_config() {
  echo "Checking for pkg-config..."
  if
    ! command -v pkg-config &
    >/dev/null
  then
    echo "pkg-config not found. Installing pkg-config..."
    if [ "$OS" = "Darwin" ]; then
      brew install pkg-config
    fi
  else
    echo "pkg-config is already installed."
  fi
}

install_with_vcpkg() {
  echo "Installing asio and SFML using vcpkg..."
  ./external/vcpkg/bootstrap-vcpkg.sh
  ./external/vcpkg/vcpkg install asio sfml
}

install_doxygen() {
  echo "Installing Doxygen using the system's package manager..."
  if [ "$OS" = "Darwin" ]; then
    brew install doxygen
  elif [ "$OS" = "Linux" ]; then
    if grep -q 'ID=ubuntu' /etc/os-release; then
      sudo apt-get install -y doxygen
    elif grep -q 'ID=fedora' /etc/os-release; then
      sudo dnf install -y doxygen
    fi
  fi
}

install_clang() {
  echo "Installing Clang-format..."
  if [ "$OS" = "Darwin" ]; then
    brew install clang-format
  elif [ "$OS" = "Linux" ]; then
    if grep -q 'ID=ubuntu' /etc/os-release; then
      sudo apt-get install -y clang-tools-extra
    elif grep -q 'ID=fedora' /etc/os-release; then
      sudo dnf install -y clang-tools-extra
    fi
  fi
}

install_ubuntu_dependencies() {
  echo "Installing additional dependencies for Ubuntu..."
  sudo apt-get install -y libudev-dev libx11-dev libxrandr-dev libxcursor-dev libxi-dev libgl1-mesa-dev autoconf libtool
}

install_fedora_dependencies() {
  echo "Installing additional dependencies for Fedora..."
  sudo dnf install -y libudev-devel libX11-devel libXrandr-devel libXcursor-devel libXi-devel mesa-libGL-devel autoconf libtool
}

OS=$(uname -s)

if [ "$OS" = "Darwin" ]; then
  echo "macOS detected. Installing dependencies..."
  install_cmake
  install_pkg_config
  install_with_vcpkg
  install_doxygen
  install_clang
elif [ "$OS" = "Linux" ]; then
  if grep -q 'ID=ubuntu' /etc/os-release; then
    echo "Ubuntu detected. Installing dependencies..."
    install_ubuntu_dependencies
    install_cmake
    install_with_vcpkg
    install_doxygen
    install_clang
  elif grep -q 'ID=fedora' /etc/os-release; then
    echo "Fedora detected. Installing dependencies..."
    install_fedora_dependencies
    install_cmake
    install_with_vcpkg
    install_doxygen
    install_clang
  else
    echo "Neither Ubuntu nor Fedora detected. Exiting..."
    exit 1
  fi
else
  echo "Unsupported operating system: $OS"
  exit 1
fi

echo "Starting build process..."
./scripts/linux_macos/build.sh
