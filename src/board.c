#include "board.h"
#include "textures.h" // Include textures.h for access to color variables
#include "config.h"

void DrawChessboard(void) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Color squareColor = ((row + col) % 2 == 0) ? lightSquareColor : darkSquareColor;
            DrawRectangle(col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, squareColor);
        }
    }
}

void InitializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    // Set up the initial board state.
    for (int col = 0; col < BOARD_SIZE; ++col) {
        board[1][col] = 1; // White pawns
        board[6][col] = 7; // Black pawns
    }
    board[0][0] = 2; // White rook
    board[0][7] = 2;
    board[7][0] = 8; // Black rook
    board[7][7] = 8;
    board[0][1] = 3; // White knight
    board[0][6] = 3;
    board[7][1] = 9; // Black knight
    board[7][6] = 9;
    board[0][2] = 4; // White bishop
    board[0][5] = 4;
    board[7][2] = 10; // Black bishop
    board[7][5] = 10;
    board[0][3] = 5; // White queen
    board[0][4] = 6; // White king
    board[7][3] = 11; // Black queen
    board[7][4] = 12; // Black king

    for (int row = 2; row < 6; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = 0; // Empty squares
        }
    }
}