#include "raylib.h"
#include "board.h"
#include "pieces.h"
#include "textures.h"
#include "config.h" // Include config.h
#include <stdio.h>


// --- Global Variables ---
int board[BOARD_SIZE][BOARD_SIZE];

int main(void) {
    // --- Initialization ---
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Chess");
    SetTargetFPS(60);

    LoadGameTextures();
    InitializeBoard(board); // Pass the board array

    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        // --- Drawing ---
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawChessboard();
        DrawPieces(board); // Pass the board array
        EndDrawing();
        // --- Input ---
        // Add input handling here
        // --- Logic ---
        // Add game logic here
    }

    // --- Cleanup ---
    UnloadGameTextures();
    CloseWindow();

    return 0;
}