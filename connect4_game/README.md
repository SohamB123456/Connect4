# Advanced Connect 4 Game in C++

A sophisticated Connect 4 game implementation demonstrating **Breadth-First Search (BFS)**, **Linked Lists**, and **Modular Class Design** in C++.

## Features

### Core Game Features
- Two-player game (Human vs AI)
- 6x7 game board (standard Connect 4 size)
- Win detection for horizontal, vertical, and diagonal connections
- Draw detection when board is full
- Input validation and error handling
- Interactive game menu with multiple commands

### Advanced Features
- **Breadth-First Search (BFS)** AI algorithm for move evaluation
- **Linked List** data structures using template Node class
- **Modular Class Design** with separate concerns
- **Minimax Algorithm** with alpha-beta pruning for AI decision making
- **Game State Analysis** with position evaluation
- **Move History** tracking and analysis
- **Configurable AI Difficulty** levels
- **Real-time Game Information** display

## Files

- `Node.h` - Template Node class for linked list implementation
- `GameState.cpp` - GameState class with BFS search capabilities
- `AIPlayer.h` / `AIPlayer.cpp` - AI player using BFS and minimax algorithms
- `Connect4.h` / `Connect4.cpp` - Main game class with modular design
- `main.cpp` - Game loop with human vs AI interface
- `Makefile` - Build configuration
- `README.md` - This documentation

## How to Compile and Run

### Using Make (Recommended)
```bash
# Compile the game
make

# Run the game
make run

# Or run directly
./connect4
```

### Manual Compilation
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o connect4 main.cpp Connect4.cpp
./connect4
```

## How to Play

1. Run the executable: `./connect4`
2. Choose between playing with AI or demonstrating BFS algorithm
3. Players take turns entering column numbers (1-7)
4. The piece will drop to the lowest available position in that column
5. First player to get 4 pieces in a row (horizontally, vertically, or diagonally) wins!
6. Use various commands for game control and analysis

## Game Controls

- **1-7**: Drop piece in column 1-7
- **q**: Quit the game
- **r**: Reset the current game
- **i**: Show game information (position score, valid moves)
- **h**: Show move history
- **a**: Toggle AI on/off
- **d**: Change AI difficulty (1-6)
- **m**: Show menu
- **y/n**: Play again after game ends

## Technical Implementation

### Breadth-First Search (BFS)
The AI uses BFS to explore game states and evaluate potential moves:
- Explores all possible moves up to a configurable depth
- Uses a queue-based approach for systematic state exploration
- Implements state hashing for efficient duplicate detection
- Evaluates positions using heuristic scoring

### Linked List Implementation
- Template-based Node class for generic data storage
- Used for maintaining game state history
- Demonstrates proper memory management with smart pointers
- Supports bidirectional traversal

### Modular Class Design
- **Connect4**: Main game controller and interface
- **GameState**: Represents board states with evaluation methods
- **AIPlayer**: Handles AI decision making using BFS and minimax
- **Node**: Generic linked list node for data structures
- Clear separation of concerns and single responsibility principle

## Makefile Targets

- `make` or `make all` - Build the game
- `make run` - Build and run the game
- `make clean` - Remove object files and executable
- `make debug` - Build with debug symbols
- `make install` - Install to /usr/local/bin
- `make uninstall` - Remove from /usr/local/bin
- `make help` - Show available targets

## Requirements

- C++11 compatible compiler (g++, clang++, etc.)
- Make (optional, for using Makefile)

## Game Rules

- Players alternate turns
- Each turn, a player drops one piece into a column
- The piece falls to the lowest available position in that column
- The first player to get 4 of their pieces in a row wins
- If the board fills up without a winner, it's a draw
