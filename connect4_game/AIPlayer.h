#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Node.h"
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

// AI Player class using BFS for move evaluation
class AIPlayer {
private:
    char playerSymbol;
    int maxDepth;
    
    // Hash function for GameState to use in unordered_set
    struct GameStateHash {
        size_t operator()(const GameState& state) const {
            size_t hash = 0;
            const vector<vector<char>>& board = state.getBoard();
            
            for (int row = 0; row < 6; row++) {
                for (int col = 0; col < 7; col++) {
                    hash = hash * 31 + static_cast<size_t>(board[row][col]);
                }
            }
            return hash;
        }
    };
    
    // Equality function for GameState
    struct GameStateEqual {
        bool operator()(const GameState& a, const GameState& b) const {
            const vector<vector<char>>& boardA = a.getBoard();
            const vector<vector<char>>& boardB = b.getBoard();
            
            for (int row = 0; row < 6; row++) {
                for (int col = 0; col < 7; col++) {
                    if (boardA[row][col] != boardB[row][col]) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

public:
    // Constructor
    AIPlayer(char symbol, int depth = 4) : playerSymbol(symbol), maxDepth(depth) {}
    
    // Get the best move using BFS with evaluation
    int getBestMove(const GameState& currentState);
    
    // BFS search to evaluate all possible moves
    int bfsEvaluate(const GameState& startState);
    
    // Minimax algorithm with alpha-beta pruning
    int minimax(const GameState& state, int depth, bool isMaximizing, int alpha, int beta);
    
    // Get all possible moves for current state
    vector<int> getPossibleMoves(const GameState& state);
    
    // Evaluate a specific move
    int evaluateMove(const GameState& state, int move);
    
    // Check if a move leads to immediate win
    bool isWinningMove(const GameState& state, int move);
    
    // Check if a move blocks opponent's winning move
    bool isBlockingMove(const GameState& state, int move);
};

#endif
