#include <iostream>

using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Template function to toggle between two values
template <typename T>
T togglePlayer(T current, T option1, T option2) {
    return (current == option1) ? option2 : option1;
}

// Display the game board
void displayBoard(const char board[9]) {
    cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n";
        if (i < 6) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Check if the move is valid
bool isValidMove(const char board[9], int move) {
    return (move >= 0 && move < 9 && board[move] != PLAYER_X && board[move] != PLAYER_O);
}

// Check for a win condition
bool checkWin(const char board[9], char player) {
    const int winningPositions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    
    for (auto& pos : winningPositions) {
        if (board[pos[0]] == player && board[pos[1]] == player && board[pos[2]] == player) {
            return true;
        }
    }
    return false;
}

// Check if the board is full (draw condition)
bool isDraw(const char board[9]) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] != PLAYER_X && board[i] != PLAYER_O) {
            return false;
        }
    }
    return true;
}

// Play the Tic-Tac-Toe game
void playGame() {
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = PLAYER_X;
    bool gameOver = false;
    
    while (!gameOver) {
        displayBoard(board);
        
        // Get move input
        int move;
        cout << "Player " << currentPlayer << ", enter a cell number (1-9): ";
        cin >> move;
        move -= 1; // Adjust for 0-based index
        
        // Validate move
        if (!isValidMove(board, move)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        
        // Make the move
        board[move] = currentPlayer;
        
        // Check win or draw
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            // Switch player using the template function
            currentPlayer = togglePlayer(currentPlayer, PLAYER_X, PLAYER_O);
        }
    }
}

// Main function
int main() {
    char playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "Thanks for playing Tic-Tac-Toe!\n";
    return 0;
}
