#!/bin/sh
set -e

echo "Building sgit..."
gcc -Wall -Wextra -O2  *.c -o sgit
mkdir -p ~/.local/bin
rm -f ~/.local/bin/sgit
cp sgit ~/.local/bin/

echo "Build complete"
