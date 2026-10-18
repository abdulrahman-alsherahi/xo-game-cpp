#ifndef GAME_H
#define GAME_H

// Game logic for the GUI version.
// It does not know anything about SFML, it only stores and checks the board.

struct Game {
    char board[9];       // 'X', 'O' or ' ' (empty)
    char currentPlayer;  // 'X' or 'O'
    bool gameOver;
    char winner;         // 'X', 'O' or ' ' (no winner / draw)
    int winLine[3];      // the 3 winning cells, -1 if there is no winner
};

void resetGame(Game& game);

// Places the current player's symbol in cell 0-8.
// Returns false if the move is not allowed (cell taken or game over).
bool makeMove(Game& game, int cell);

#endif
