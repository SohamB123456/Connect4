#include "AIPlayer.h"
#include <algorithm>
#include <climits>

int AIPlayer::getBestMove(const GameState& currentState) {
    // First check for immediate winning moves
    for (int col = 0; col < 7; col++) {
        if (isWinningMove(currentState, col)) {
            return col;
        }
    }
    
    // Then check for moves that block opponent's winning moves
    for (int col = 0; col < 7; col++) {
        if (isBlockingMove(currentState, col)) {
            return col;
        }
    }
    
    // Use minimax for deeper analysis
    int bestMove = 3; // Default to center column
    int bestScore = INT_MIN;
    
    vector<int> possibleMoves = getPossibleMoves(currentState);
    
    for (int move : possibleMoves) {
        int score = evaluateMove(currentState, move);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    
    return bestMove;
}

int AIPlayer::bfsEvaluate(const GameState& startState) {
    queue<GameState> bfsQueue;
    unordered_set<GameState, GameStateHash, GameStateEqual> visited;
    
    bfsQueue.push(startState);
    visited.insert(startState);
    
    int bestScore = INT_MIN;
    int nodesExplored = 0;
    
    while (!bfsQueue.empty() && nodesExplored < 1000) { // Limit exploration
        GameState current = bfsQueue.front();
        bfsQueue.pop();
        nodesExplored++;
        
        // Evaluate current state
        int currentScore = current.evaluateState();
        if (currentScore > bestScore) {
            bestScore = currentScore;
        }
        
        // If we've reached max depth, don't explore further
        if (current.getDepth() >= maxDepth) {
            continue;
        }
        
        // Generate next states
        char nextPlayer = (current.getLastPlayer() == 'X') ? 'O' : 'X';
        vector<GameState> nextStates = current.generateNextStates(nextPlayer);
        
        for (const GameState& nextState : nextStates) {
            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                bfsQueue.push(nextState);
            }
        }
    }
    
    return bestScore;
}

int AIPlayer::minimax(const GameState& state, int depth, bool isMaximizing, int alpha, int beta) {
    // Base cases
    if (depth == 0 || state.isWinningState() || state.isDrawState()) {
        return state.evaluateState();
    }
    
    if (isMaximizing) {
        int maxEval = INT_MIN;
        vector<GameState> nextStates = state.generateNextStates('O');
        
        for (const GameState& nextState : nextStates) {
            int eval = minimax(nextState, depth - 1, false, alpha, beta);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            
            if (beta <= alpha) {
                break; // Beta cutoff
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        vector<GameState> nextStates = state.generateNextStates('X');
        
        for (const GameState& nextState : nextStates) {
            int eval = minimax(nextState, depth - 1, true, alpha, beta);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            
            if (beta <= alpha) {
                break; // Alpha cutoff
            }
        }
        return minEval;
    }
}

vector<int> AIPlayer::getPossibleMoves(const GameState& state) {
    vector<int> moves;
    
    for (int col = 0; col < 7; col++) {
        if (state.isValidMove(col)) {
            moves.push_back(col);
        }
    }
    
    return moves;
}

int AIPlayer::evaluateMove(const GameState& state, int move) {
    GameState nextState = state.makeMove(move, playerSymbol);
    
    // Use minimax to evaluate this move
    int score = minimax(nextState, maxDepth - 1, false, INT_MIN, INT_MAX);
    
    // Prefer center columns
    if (move == 3) score += 10;
    else if (move == 2 || move == 4) score += 5;
    else if (move == 1 || move == 5) score += 2;
    
    return score;
}

bool AIPlayer::isWinningMove(const GameState& state, int move) {
    if (!state.isValidMove(move)) {
        return false;
    }
    
    GameState nextState = state.makeMove(move, playerSymbol);
    return nextState.isWinningState();
}

bool AIPlayer::isBlockingMove(const GameState& state, int move) {
    if (!state.isValidMove(move)) {
        return false;
    }
    
    char opponent = (playerSymbol == 'X') ? 'O' : 'X';
    GameState nextState = state.makeMove(move, opponent);
    return nextState.isWinningState();
}
