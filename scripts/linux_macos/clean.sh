#!/bin/bash

set -e

cd "$(dirname "$0")/../../"

echo "Cleaning up..."

if [ -d "build" ]; then
    rm -rf build/
    echo "Removed build directory."
fi

if [ -f "r-type_client" ]; then
    rm r-type_client
    echo "Removed r-type_client executable."
fi

if [ -f "r-type_server" ]; then
    rm r-type_server
    echo "Removed r-type_server executable."
fi

echo "Clean completed."
