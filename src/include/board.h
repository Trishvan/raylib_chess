#ifndef BOARD_H
#define BOARD_H

#include "linked_list.h"
#include "raylib.h"
#include "pieces.h"  // Include pieces.h for the definition of Piece

typedef struct square {
    int row;
    int col;
    Color c;
    Piece* resident;  // Should be Piece*, as Piece is defined in pieces.h
} Square;

typedef struct {
    int fromRow, fromCol;
    int toRow, toCol;
    Piece* captured;  // Optional: NULL if no capture
} Move;

void InitBoard(void);
void DrawBoard(void);
void UpdateBoard(void);
Square* GetSquareAt(int, int);
Square* GetSquare(int index);

#endif // BOARD_H
