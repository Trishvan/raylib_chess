#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include "config.h" // Include config.h

// --- Function Declarations ---
void DrawChessboard(void);
void InitializeBoard(int board[BOARD_SIZE][BOARD_SIZE]);

#endif