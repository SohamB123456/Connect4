#!/bin/bash

echo "=========================================="
echo "    Connect 4 Advanced Features Demo"
echo "=========================================="
echo ""

echo "1. Compiling the game..."
make clean
make
echo "Compilation complete!"
echo ""

echo "2. Running BFS Algorithm Demonstration..."
echo "2" | ./connect4
echo ""

echo "3. Starting Interactive Game..."
echo "   (Press Ctrl+C to exit the game)"
echo ""
./connect4
