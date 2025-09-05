# Advanced Connect 4 Game in C++

A sophisticated Connect 4 game implementation demonstrating **Breadth-First Search (BFS)**, **Linked Lists**, and **Modular Class Design** in C++.

## Features

### Game Features
- Two-player game 
- 6x7 game board 
- Draw detection when board is full
- Input validation and error handling
- Interactive game menu

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


## Game Rules

- Players alternate turns
- Each turn, a player drops one piece into a column
- The piece falls to the lowest available position in that column
- The first player to get 4 of their pieces in a row wins
- If the board fills up without a winner, it's a draw
