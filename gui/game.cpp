#include "game.h"

// All 8 ways to win: 3 rows, 3 columns, 2 diagonals
// (the same checks as checkWin() in the console version)
const int lines[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};

void resetGame(Game& game) {
    for (int i = 0; i < 9; i++) {
        game.board[i] = ' ';
    }
    game.currentPlayer = 'X';
    game.gameOver = false;
    game.winner = ' ';
    for (int i = 0; i < 3; i++) {
        game.winLine[i] = -1;
    }
}

// Returns the index of the winning line, or -1 if nobody has won
int findWinLine(const char b[9]) {
    for (int i = 0; i < 8; i++) {
        int a = lines[i][0];
        int c = lines[i][1];
        int d = lines[i][2];
        if (b[a] != ' ' && b[a] == b[c] && b[c] == b[d]) {
            return i;
        }
    }
    return -1;
}

bool isBoardFull(const char b[9]) {
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool makeMove(Game& game, int cell) {
    if (game.gameOver || cell < 0 || cell > 8 || game.board[cell] != ' ') {
        return false;
    }

    game.board[cell] = game.currentPlayer;

    int line = findWinLine(game.board);
    if (line != -1) {
        game.winner = game.currentPlayer;
        game.gameOver = true;
        for (int i = 0; i < 3; i++) {
            game.winLine[i] = lines[line][i];
        }
    }
    else if (isBoardFull(game.board)) {
        game.gameOver = true;  // draw
    }
    else {
        game.currentPlayer = (game.currentPlayer == 'X') ? 'O' : 'X';
    }

    return true;
}
