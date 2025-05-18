#!/bin/sh

DIRECTORIES="server client libs common"

PATTERNS="*.cpp *.hpp"

echo "Running clang-format..."

for dir in $DIRECTORIES; do
    for pattern in $PATTERNS; do
        if [ -d "$dir" ]; then
            find "$dir" -name "$pattern" -exec clang-format -i {} +
        else
            echo "Warning: Directory $dir does not exist."
        fi
    done
done

echo "Formatting complete."
