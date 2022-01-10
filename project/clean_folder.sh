#!/bin/sh
find $1 \( -name "*.h" -o -name "*.cpp" -o -name "*.hpp" -o -name "*.c" \) -exec ./build/mvcodecleaner.exe {} \;
