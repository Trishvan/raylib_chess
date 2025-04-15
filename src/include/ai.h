#ifndef AI_H
#define AI_H

#include "board.h"
#include "pieces.h"

typedef struct {
    Square** data; // Array of Square* (pointer to Square pointers)
    int size;      // Number of attacking squares
} AttackingSquares;


// Function to initialize AI-related structures
void InitAI(void);

// Function to handle AI's move logic
void MakeMove(Move m);  // Declare the MakeMove function

Move GetRandomMove(int side);

// Function to evaluate all possible moves for the AI
Move* GetPossibleMoves(Piece* piece);

// Function to randomly select a move for the AI
void MakeRandomMove(void);

// Function to update AI's available moves
void UpdateAIMoves(void);

// Function to clean up AI resources
void DestroyAI(void);

#endif // AI_H
