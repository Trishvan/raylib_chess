#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "board.h"
#include "pieces.h"
#include "consts.h"

extern Square* squares; // Assuming squares are defined and initialized elsewhere

// Generate all legal moves for a given side
void GenerateAllMoves(int side, Move* moves, int* moveCount) {
    *moveCount = 0;
    for (int i = 0; i < NUM_ROWS * NUM_COLS; i++) {
        Square* sq = &squares[i];
        Piece* p = sq->resident;
        if (p && p->side == side) {
            // Ensure the attacking squares are properly initialized
            if (p->attacking && p->attacking->data) {
                for (int j = 0; j < p->attacking->size; j++) {
                    // Correct casting from void* to Square*
                    Square* target = (Square*)p->attacking->data[j];
                    Move m = {
                        .fromRow = sq->row,
                        .fromCol = sq->col,
                        .toRow = target->row,
                        .toCol = target->col,
                        .captured = target->resident
                    };
                    moves[(*moveCount)++] = m;
                }
            }
        }
    }
}

// Get a random legal move for a given side
Move GetRandomMove(int side) {
    Move moves[256]; // Assume a maximum of 256 moves
    int moveCount = 0;
    GenerateAllMoves(side, moves, &moveCount);
    if (moveCount == 0) {
        printf("AI has no legal moves.\n");
        exit(0);
    }
    return moves[rand() % moveCount];
}

// Make the move and update the board
void MakeMove(Move m) {
    Square* from = &squares[m.fromRow * NUM_COLS + m.fromCol];
    Square* to = &squares[m.toRow * NUM_COLS + m.toCol];
    
    // Save the captured piece and update the move struct
    Piece* capturedPiece = to->resident;  // Store captured piece
    to->resident = from->resident; // Move the piece to the target square
    from->resident = NULL; // Remove the piece from the original square
    m.captured = capturedPiece; // Set the captured piece in the move

    UpdateBoard(); // Update the board after making the move
}

// Function to initialize AI-related structures
void InitAI(void) {
    // Initialize AI resources, if any
    srand(time(NULL)); // Seed random number generator for random moves
}

// Function to clean up AI resources
void DestroyAI(void) {
    // Free AI-related resources, if any
}
