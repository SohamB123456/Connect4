#ifndef CONNECT4_H
#define CONNECT4_H

#include "Node.h"
#include "AIPlayer.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Enhanced Connect4 class with modular design
class Connect4 {
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    
    vector<vector<char>> board;
    char currentPlayer;
    bool gameOver;
    char winner;
    GameState currentState;
    unique_ptr<AIPlayer> aiPlayer;
    bool aiEnabled;
    
    // Helper methods
    bool isValidMove(int col) const;
    bool makeMove(int col);
    bool checkWin(int row, int col) const;
    bool checkHorizontal(int row, int col) const;
    bool checkVertical(int row, int col) const;
    bool checkDiagonal(int row, int col) const;
    bool isBoardFull() const;
    int getNextEmptyRow(int col) const;
    void updateGameState();
    void switchPlayer();

public:
    // Constructor
    Connect4(bool enableAI = true);
    
    // Game control methods
    void displayBoard() const;
    bool playMove(int col);
    bool playAIMove();
    bool isGameOver() const;
    char getWinner() const;
    char getCurrentPlayer() const;
    void resetGame();
    string getGameStatus() const;
    
    // AI control methods
    void enableAI(bool enable);
    bool isAIEnabled() const;
    void setAIDifficulty(int depth);
    
    // Game state methods
    GameState getCurrentGameState() const;
    vector<GameState> getGameHistory() const;
    
    // Analysis methods
    int evaluateCurrentPosition() const;
    vector<int> getValidMoves() const;
    bool isWinningMove(int col);
    bool isBlockingMove(int col);
    
    // Display methods
    void displayGameInfo() const;
    void displayMoveHistory() const;
};

#endif