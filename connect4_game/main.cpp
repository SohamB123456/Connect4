#include "Connect4.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>

using namespace std;

void displayWelcome() {
    cout << "========================================" << endl;
    cout << "    Advanced Connect 4 with AI!" << endl;
    cout << "========================================" << endl;
    cout << "Features:" << endl;
    cout << "- Breadth-First Search (BFS) AI" << endl;
    cout << "- Linked List Data Structures" << endl;
    cout << "- Modular Class Design" << endl;
    cout << "- Move Evaluation & Analysis" << endl;
    cout << "========================================" << endl;
}

void displayInstructions() {
    cout << "\nInstructions:" << endl;
    cout << "- Enter a column number (1-7) to drop your piece" << endl;
    cout << "- You are Player X, AI is Player O" << endl;
    cout << "- Get 4 pieces in a row to win!" << endl;
    cout << "- Type 'q' to quit, 'r' to reset, 'i' for info" << endl;
    cout << "- Type 'h' for move history, 'a' to toggle AI" << endl;
    cout << "========================================" << endl;
}

void displayMenu() {
    cout << "\n=== Game Menu ===" << endl;
    cout << "1-7: Make a move" << endl;
    cout << "q: Quit game" << endl;
    cout << "r: Reset game" << endl;
    cout << "i: Show game info" << endl;
    cout << "h: Show move history" << endl;
    cout << "a: Toggle AI on/off" << endl;
    cout << "d: Change AI difficulty" << endl;
    cout << "=================" << endl;
}

int getPlayerInput(Connect4& game) {
    int choice;
    string input;
    
    while (true) {
        cout << "\nPlayer " << game.getCurrentPlayer() << ", enter your move: ";
        cin >> input;
        
        // Check for special commands
        if (input == "q" || input == "Q") {
            return -1; // Quit
        }
        if (input == "r" || input == "R") {
            return -2; // Reset
        }
        if (input == "i" || input == "I") {
            game.displayGameInfo();
            continue;
        }
        if (input == "h" || input == "H") {
            game.displayMoveHistory();
            continue;
        }
        if (input == "a" || input == "A") {
            game.enableAI(!game.isAIEnabled());
            cout << "AI " << (game.isAIEnabled() ? "enabled" : "disabled") << endl;
            continue;
        }
        if (input == "d" || input == "D") {
            cout << "Enter AI difficulty (1-6): ";
            int difficulty;
            cin >> difficulty;
            if (difficulty >= 1 && difficulty <= 6) {
                game.setAIDifficulty(difficulty);
                cout << "AI difficulty set to " << difficulty << endl;
            } else {
                cout << "Invalid difficulty level!" << endl;
            }
            continue;
        }
        if (input == "m" || input == "M") {
            displayMenu();
            continue;
        }
        
        // Try to convert to integer
        try {
            choice = stoi(input);
            if (choice >= 1 && choice <= 7) {
                return choice - 1; // Convert to 0-based index
            } else {
                cout << "Please enter a number between 1 and 7." << endl;
            }
        } catch (const invalid_argument&) {
            cout << "Invalid input. Please enter a number between 1 and 7, or a command (q/r/i/h/a/d)." << endl;
        }
    }
}

void simulateThinking() {
    cout << "AI is thinking";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
}

void playGame() {
    Connect4 game(true); // Enable AI by default
    bool playing = true;
    
    displayWelcome();
    displayInstructions();
    
    while (playing) {
        game.displayBoard();
        game.displayGameInfo();
        
        if (game.getCurrentPlayer() == 'X') {
            // Human player's turn
            int column = getPlayerInput(game);
            
            if (column == -1) { // Quit
                cout << "\nThanks for playing! Goodbye!" << endl;
                break;
            } else if (column == -2) { // Reset
                game.resetGame();
                cout << "\nGame reset! Starting over..." << endl;
                continue;
            }
            
            // Try to make the move
            if (game.playMove(column)) {
                cout << "Move successful!" << endl;
            } else {
                cout << "Invalid move! That column is full. Please try again." << endl;
                continue;
            }
        } else {
            // AI player's turn
            cout << "\nAI's turn..." << endl;
            simulateThinking();
            
            if (game.playAIMove()) {
                cout << "AI made its move!" << endl;
            } else {
                cout << "AI failed to make a move!" << endl;
                break;
            }
        }
        
        // Check if game is over
        if (game.isGameOver()) {
            game.displayBoard();
            cout << "\n" << game.getGameStatus() << endl;
            
            // Display final analysis
            cout << "\n=== Final Analysis ===" << endl;
            cout << "Final position score: " << game.evaluateCurrentPosition() << endl;
            game.displayMoveHistory();
            
            cout << "\nWould you like to play again? (y/n): ";
            char playAgain;
            cin >> playAgain;
            
            if (playAgain == 'y' || playAgain == 'Y') {
                game.resetGame();
                cout << "\nNew game started!" << endl;
            } else {
                cout << "\nThanks for playing! Goodbye!" << endl;
                playing = false;
            }
        }
    }
}

void demonstrateBFS() {
    cout << "\n=== BFS Demonstration ===" << endl;
    cout << "Creating a sample game state and demonstrating BFS search..." << endl;
    
    Connect4 demoGame(false); // Disable AI for demo
    
    // Make some sample moves
    demoGame.playMove(3); // Center
    demoGame.playMove(2);
    demoGame.playMove(3);
    demoGame.playMove(2);
    demoGame.playMove(3);
    
    cout << "Sample board state:" << endl;
    demoGame.displayBoard();
    
    cout << "Position evaluation: " << demoGame.evaluateCurrentPosition() << endl;
    
    vector<int> validMoves = demoGame.getValidMoves();
    cout << "Valid moves: ";
    for (int move : validMoves) {
        cout << move + 1 << " ";
    }
    cout << endl;
    
    cout << "BFS analysis complete!" << endl;
    cout << "=======================" << endl;
}

int main() {
    cout << "Choose an option:" << endl;
    cout << "1. Play Connect 4 with AI" << endl;
    cout << "2. Demonstrate BFS Algorithm" << endl;
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        playGame();
    } else if (choice == 2) {
        demonstrateBFS();
    } else {
        cout << "Invalid choice. Starting game..." << endl;
        playGame();
    }
    
    return 0;
}