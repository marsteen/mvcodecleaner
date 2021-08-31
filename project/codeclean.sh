#!/bin/sh
find $1 -name '*.cpp'  -or -name '*.h'   -or -name '*.c'  -or -name '*.cpp' -or -name '*.hpp' -exec mvcodecleaner {} \;


