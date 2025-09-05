#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

// Node class for linked list implementation
template<typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;

public:
    // Constructor
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    
    // Destructor
    ~Node() = default;
    
    // Getters
    T getData() const { return data; }
    Node<T>* getNext() const { return next; }
    Node<T>* getPrev() const { return prev; }
    
    // Setters
    void setData(T value) { data = value; }
    void setNext(Node<T>* node) { next = node; }
    void setPrev(Node<T>* node) { prev = node; }
};

// GameState class to represent a board state
class GameState {
private:
    vector<vector<char>> board;
    int lastMoveRow;
    int lastMoveCol;
    char lastPlayer;
    int depth;
    int score;

public:
    // Constructor
    GameState(const vector<vector<char>>& b, int row = -1, int col = -1, char player = ' ', int d = 0, int s = 0)
        : board(b), lastMoveRow(row), lastMoveCol(col), lastPlayer(player), depth(d), score(s) {}
    
    // Copy constructor
    GameState(const GameState& other)
        : board(other.board), lastMoveRow(other.lastMoveRow), lastMoveCol(other.lastMoveCol),
          lastPlayer(other.lastPlayer), depth(other.depth), score(other.score) {}
    
    // Assignment operator
    GameState& operator=(const GameState& other) {
        if (this != &other) {
            board = other.board;
            lastMoveRow = other.lastMoveRow;
            lastMoveCol = other.lastMoveCol;
            lastPlayer = other.lastPlayer;
            depth = other.depth;
            score = other.score;
        }
        return *this;
    }
    
    // Getters
    vector<vector<char>> getBoard() const { return board; }
    int getLastMoveRow() const { return lastMoveRow; }
    int getLastMoveCol() const { return lastMoveCol; }
    char getLastPlayer() const { return lastPlayer; }
    int getDepth() const { return depth; }
    int getScore() const { return score; }
    
    // Setters
    void setScore(int s) { score = s; }
    void setDepth(int d) { depth = d; }
    
    // Check if this state represents a winning position
    bool isWinningState() const;
    
    // Check if this state represents a draw
    bool isDrawState() const;
    
    // Evaluate the state for AI decision making
    int evaluateState() const;
    
    // Generate all possible next states
    vector<GameState> generateNextStates(char player) const;
    
    // Check if a move is valid
    bool isValidMove(int col) const;
    
    // Make a move and return new state
    GameState makeMove(int col, char player) const;
    
    // Check for win condition
    bool checkWin(int row, int col) const;
    bool checkHorizontal(int row, int col) const;
    bool checkVertical(int row, int col) const;
    bool checkDiagonal(int row, int col) const;
};

#endif
