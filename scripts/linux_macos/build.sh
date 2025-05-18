#!/bin/bash

cmake -B build -S .
cmake --build build

if [ $? -eq 0 ]; then
    mv build/server/r-type_server . && mv build/client/r-type_client .
    echo "Build completed successfully."
else
    echo "Build failed."
fi
