#include "Connect4.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>

Connect4::Connect4(bool enableAI) : currentPlayer('X'), gameOver(false), winner(' '), 
    currentState(vector<vector<char>>(ROWS, vector<char>(COLS, ' '))), aiEnabled(enableAI) {
    
    // Initialize the board with empty spaces
    board.resize(ROWS, vector<char>(COLS, ' '));
    
    // Initialize AI player if enabled
    if (aiEnabled) {
        aiPlayer = unique_ptr<AIPlayer>(new AIPlayer('O', 4));
    }
    
    updateGameState();
}

void Connect4::displayBoard() const {
    cout << "\n";
    cout << "  1   2   3   4   5   6   7" << endl;
    cout << "+---+---+---+---+---+---+---+" << endl;
    
    for (int row = 0; row < ROWS; row++) {
        cout << "|";
        for (int col = 0; col < COLS; col++) {
            cout << " " << board[row][col] << " |";
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+---+" << endl;
    }
    cout << "\n";
}

bool Connect4::isValidMove(int col) const {
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

int Connect4::getNextEmptyRow(int col) const {
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            return row;
        }
    }
    return -1;
}

bool Connect4::makeMove(int col) {
    if (!isValidMove(col)) {
        return false;
    }
    
    int row = getNextEmptyRow(col);
    board[row][col] = currentPlayer;
    
    // Check for win after the move
    if (checkWin(row, col)) {
        gameOver = true;
        winner = currentPlayer;
    } else if (isBoardFull()) {
        gameOver = true;
        winner = ' '; // Draw
    } else {
        switchPlayer();
    }
    
    updateGameState();
    return true;
}

bool Connect4::playMove(int col) {
    return makeMove(col);
}

bool Connect4::playAIMove() {
    if (!aiEnabled || !aiPlayer || currentPlayer != 'O') {
        return false;
    }
    
    int bestMove = aiPlayer->getBestMove(currentState);
    return makeMove(bestMove);
}

bool Connect4::checkWin(int row, int col) const {
    return checkHorizontal(row, col) || checkVertical(row, col) || checkDiagonal(row, col);
}

bool Connect4::checkHorizontal(int row, int col) const {
    char player = board[row][col];
    int count = 1;
    
    // Check left
    for (int c = col - 1; c >= 0 && board[row][c] == player; c--) {
        count++;
    }
    
    // Check right
    for (int c = col + 1; c < COLS && board[row][c] == player; c++) {
        count++;
    }
    
    return count >= 4;
}

bool Connect4::checkVertical(int row, int col) const {
    char player = board[row][col];
    int count = 1;
    
    // Check up
    for (int r = row - 1; r >= 0 && board[r][col] == player; r--) {
        count++;
    }
    
    // Check down
    for (int r = row + 1; r < ROWS && board[r][col] == player; r++) {
        count++;
    }
    
    return count >= 4;
}

bool Connect4::checkDiagonal(int row, int col) const {
    char player = board[row][col];
    
    // Check diagonal (top-left to bottom-right)
    int count1 = 1;
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0 && board[r][c] == player; r--, c--) {
        count1++;
    }
    for (int r = row + 1, c = col + 1; r < ROWS && c < COLS && board[r][c] == player; r++, c++) {
        count1++;
    }
    
    // Check diagonal (top-right to bottom-left)
    int count2 = 1;
    for (int r = row - 1, c = col + 1; r >= 0 && c < COLS && board[r][c] == player; r--, c++) {
        count2++;
    }
    for (int r = row + 1, c = col - 1; r < ROWS && c >= 0 && board[r][c] == player; r++, c--) {
        count2++;
    }
    
    return count1 >= 4 || count2 >= 4;
}

bool Connect4::isBoardFull() const {
    for (int col = 0; col < COLS; col++) {
        if (board[0][col] == ' ') {
            return false;
        }
    }
    return true;
}

bool Connect4::isGameOver() const {
    return gameOver;
}

char Connect4::getWinner() const {
    return winner;
}

char Connect4::getCurrentPlayer() const {
    return currentPlayer;
}

void Connect4::resetGame() {
    // Clear the board
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = ' ';
        }
    }
    
    currentPlayer = 'X';
    gameOver = false;
    winner = ' ';
    updateGameState();
}

string Connect4::getGameStatus() const {
    if (!gameOver) {
        return "Game in progress";
    } else if (winner == ' ') {
        return "It's a draw!";
    } else {
        return "Player " + string(1, winner) + " wins!";
    }
}

void Connect4::enableAI(bool enable) {
    aiEnabled = enable;
    if (enable && !aiPlayer) {
        aiPlayer = unique_ptr<AIPlayer>(new AIPlayer('O', 4));
    }
}

bool Connect4::isAIEnabled() const {
    return aiEnabled;
}

void Connect4::setAIDifficulty(int depth) {
    if (aiPlayer) {
        aiPlayer = unique_ptr<AIPlayer>(new AIPlayer('O', depth));
    }
}

GameState Connect4::getCurrentGameState() const {
    return currentState;
}

vector<GameState> Connect4::getGameHistory() const {
    // This would require maintaining a history of states
    // For now, return just the current state
    return {currentState};
}

int Connect4::evaluateCurrentPosition() const {
    return currentState.evaluateState();
}

vector<int> Connect4::getValidMoves() const {
    vector<int> moves;
    for (int col = 0; col < COLS; col++) {
        if (isValidMove(col)) {
            moves.push_back(col);
        }
    }
    return moves;
}

bool Connect4::isWinningMove(int col) {
    if (!isValidMove(col)) return false;
    
    int row = getNextEmptyRow(col);
    // Create a temporary board to test the move
    vector<vector<char>> tempBoard = board;
    tempBoard[row][col] = currentPlayer;
    bool isWin = checkWin(row, col);
    
    return isWin;
}

bool Connect4::isBlockingMove(int col) {
    if (!isValidMove(col)) return false;
    
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';
    int row = getNextEmptyRow(col);
    // Create a temporary board to test the move
    vector<vector<char>> tempBoard = board;
    tempBoard[row][col] = opponent;
    bool isBlock = checkWin(row, col);
    
    return isBlock;
}

void Connect4::updateGameState() {
    currentState = GameState(board);
}

void Connect4::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void Connect4::displayGameInfo() const {
    cout << "\n=== Game Information ===" << endl;
    cout << "Current Player: " << currentPlayer << endl;
    cout << "AI Enabled: " << (aiEnabled ? "Yes" : "No") << endl;
    cout << "Position Score: " << evaluateCurrentPosition() << endl;
    cout << "Valid Moves: ";
    vector<int> moves = getValidMoves();
    for (int move : moves) {
        cout << move + 1 << " ";
    }
    cout << endl;
    cout << "========================" << endl;
}

void Connect4::displayMoveHistory() const {
    cout << "\n=== Move History ===" << endl;
    cout << "Current state depth: " << currentState.getDepth() << endl;
    cout << "Last move: Row " << currentState.getLastMoveRow() 
         << ", Col " << currentState.getLastMoveCol() 
         << " by Player " << currentState.getLastPlayer() << endl;
    cout << "====================" << endl;
}