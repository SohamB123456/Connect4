#include "Node.h"
#include <algorithm>
#include <climits>

bool GameState::isWinningState() const {
    if (lastMoveRow == -1 || lastMoveCol == -1) return false;
    return checkWin(lastMoveRow, lastMoveCol);
}

bool GameState::isDrawState() const {
    // Check if all top positions are filled
    for (int col = 0; col < 7; col++) {
        if (board[0][col] == ' ') {
            return false;
        }
    }
    return !isWinningState();
}

int GameState::evaluateState() const {
    if (isWinningState()) {
        return (lastPlayer == 'O') ? 1000 : -1000; // AI wins = positive, Human wins = negative
    }
    if (isDrawState()) {
        return 0;
    }
    
    int score = 0;
    
    // Evaluate horizontal lines
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            int aiCount = 0, humanCount = 0, emptyCount = 0;
            
            for (int i = 0; i < 4; i++) {
                if (board[row][col + i] == 'O') aiCount++;
                else if (board[row][col + i] == 'X') humanCount++;
                else emptyCount++;
            }
            
            if (aiCount > 0 && humanCount == 0) {
                score += aiCount * aiCount * 10;
            } else if (humanCount > 0 && aiCount == 0) {
                score -= humanCount * humanCount * 10;
            }
        }
    }
    
    // Evaluate vertical lines
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 3; row++) {
            int aiCount = 0, humanCount = 0, emptyCount = 0;
            
            for (int i = 0; i < 4; i++) {
                if (board[row + i][col] == 'O') aiCount++;
                else if (board[row + i][col] == 'X') humanCount++;
                else emptyCount++;
            }
            
            if (aiCount > 0 && humanCount == 0) {
                score += aiCount * aiCount * 10;
            } else if (humanCount > 0 && aiCount == 0) {
                score -= humanCount * humanCount * 10;
            }
        }
    }
    
    // Evaluate diagonal lines (top-left to bottom-right)
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            int aiCount = 0, humanCount = 0, emptyCount = 0;
            
            for (int i = 0; i < 4; i++) {
                if (board[row + i][col + i] == 'O') aiCount++;
                else if (board[row + i][col + i] == 'X') humanCount++;
                else emptyCount++;
            }
            
            if (aiCount > 0 && humanCount == 0) {
                score += aiCount * aiCount * 10;
            } else if (humanCount > 0 && aiCount == 0) {
                score -= humanCount * humanCount * 10;
            }
        }
    }
    
    // Evaluate diagonal lines (top-right to bottom-left)
    for (int row = 0; row < 3; row++) {
        for (int col = 3; col < 7; col++) {
            int aiCount = 0, humanCount = 0, emptyCount = 0;
            
            for (int i = 0; i < 4; i++) {
                if (board[row + i][col - i] == 'O') aiCount++;
                else if (board[row + i][col - i] == 'X') humanCount++;
                else emptyCount++;
            }
            
            if (aiCount > 0 && humanCount == 0) {
                score += aiCount * aiCount * 10;
            } else if (humanCount > 0 && aiCount == 0) {
                score -= humanCount * humanCount * 10;
            }
        }
    }
    
    return score;
}

vector<GameState> GameState::generateNextStates(char player) const {
    vector<GameState> nextStates;
    
    for (int col = 0; col < 7; col++) {
        if (isValidMove(col)) {
            nextStates.push_back(makeMove(col, player));
        }
    }
    
    return nextStates;
}

bool GameState::isValidMove(int col) const {
    return col >= 0 && col < 7 && board[0][col] == ' ';
}

GameState GameState::makeMove(int col, char player) const {
    vector<vector<char>> newBoard = board;
    
    // Find the lowest empty row in the column
    int row = -1;
    for (int r = 5; r >= 0; r--) {
        if (newBoard[r][col] == ' ') {
            row = r;
            break;
        }
    }
    
    if (row != -1) {
        newBoard[row][col] = player;
    }
    
    return GameState(newBoard, row, col, player, depth + 1);
}

bool GameState::checkWin(int row, int col) const {
    return checkHorizontal(row, col) || checkVertical(row, col) || checkDiagonal(row, col);
}

bool GameState::checkHorizontal(int row, int col) const {
    char player = board[row][col];
    int count = 1;
    
    // Check left
    for (int c = col - 1; c >= 0 && board[row][c] == player; c--) {
        count++;
    }
    
    // Check right
    for (int c = col + 1; c < 7 && board[row][c] == player; c++) {
        count++;
    }
    
    return count >= 4;
}

bool GameState::checkVertical(int row, int col) const {
    char player = board[row][col];
    int count = 1;
    
    // Check up
    for (int r = row - 1; r >= 0 && board[r][col] == player; r--) {
        count++;
    }
    
    // Check down
    for (int r = row + 1; r < 6 && board[r][col] == player; r++) {
        count++;
    }
    
    return count >= 4;
}

bool GameState::checkDiagonal(int row, int col) const {
    char player = board[row][col];
    
    // Check diagonal (top-left to bottom-right)
    int count1 = 1;
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0 && board[r][c] == player; r--, c--) {
        count1++;
    }
    for (int r = row + 1, c = col + 1; r < 6 && c < 7 && board[r][c] == player; r++, c++) {
        count1++;
    }
    
    // Check diagonal (top-right to bottom-left)
    int count2 = 1;
    for (int r = row - 1, c = col + 1; r >= 0 && c < 7 && board[r][c] == player; r--, c++) {
        count2++;
    }
    for (int r = row + 1, c = col - 1; r < 6 && c >= 0 && board[r][c] == player; r++, c--) {
        count2++;
    }
    
    return count1 >= 4 || count2 >= 4;
}
