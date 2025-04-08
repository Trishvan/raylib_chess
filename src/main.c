#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// --- Constants ---
#define BOARD_SIZE 8
#define SQUARE_SIZE 80
#define SCREEN_WIDTH (BOARD_SIZE * SQUARE_SIZE)
#define SCREEN_HEIGHT (BOARD_SIZE * SQUARE_SIZE)

// --- Function Declarations ---
void DrawChessboard(void);
void DrawPieces(void);
void InitializeBoard(void);
Texture2D LoadPieceTexture(const char *filename);
void UnloadPieceTextures(void);
void LoadGameTextures(void);
void UnloadGameTextures(void);

// --- Global Variables ---
Texture2D checkerboardTexture;
Color lightSquareColor;
Color darkSquareColor;

// Piece textures
Texture2D whitePawnTexture;
Texture2D whiteRookTexture;
Texture2D whiteKnightTexture;
Texture2D whiteBishopTexture;
Texture2D whiteQueenTexture;
Texture2D whiteKingTexture;
Texture2D blackPawnTexture;
Texture2D blackRookTexture;
Texture2D blackKnightTexture;
Texture2D blackBishopTexture;
Texture2D blackQueenTexture;
Texture2D blackKingTexture;

// A 2D array to represent the board state.
int board[BOARD_SIZE][BOARD_SIZE];

int main(void) {
    // --- Initialization ---
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Chess");
    SetTargetFPS(60);

    LoadGameTextures(); // Load all textures
    InitializeBoard();

    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        // --- Drawing ---
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawChessboard();
        DrawPieces();
        EndDrawing();
        // --- Input ---
        // Add input handling here
        // --- Logic ---
        // Add game logic here
    }

    // --- Cleanup ---
    UnloadGameTextures(); // Unload all textures
    CloseWindow();

    return 0;
}

// --- Function Definitions ---

void LoadGameTextures(void) {
    // Load the checkerboard texture
    checkerboardTexture = LoadTexture("art/chessboard.png");
    if (checkerboardTexture.id == 0) {
        fprintf(stderr, "Error: Could not load chessboard.png!\n");
        CloseWindow();
        exit(1);
    }

    // Extract colors from the checkerboard texture
    Image checkerboardImage = LoadImageFromTexture(checkerboardTexture);
    if (checkerboardImage.data == NULL) {
        fprintf(stderr, "Error: Could not load image from texture!\n");
        CloseWindow();
        exit(1);
    }
    lightSquareColor = GetImageColor(checkerboardImage, 0, 0);
    darkSquareColor = GetImageColor(checkerboardImage, 1, 0);
    UnloadImage(checkerboardImage);

    // Load piece textures
    whitePawnTexture   = LoadPieceTexture("art/chess_piece_2_white_pawn.png");
    whiteRookTexture   = LoadPieceTexture("art/chess_piece_2_white_rook.png");
    whiteKnightTexture = LoadPieceTexture("art/chess_piece_2_white_knight.png");
    whiteBishopTexture = LoadPieceTexture("art/chess_piece_2_white_bishop.png");
    whiteQueenTexture  = LoadPieceTexture("art/chess_piece_2_white_queen.png");
    whiteKingTexture   = LoadPieceTexture("art/chess_piece_2_white_king.png");
    blackPawnTexture   = LoadPieceTexture("art/chess_piece_2_black_pawn.png");
    blackRookTexture   = LoadPieceTexture("art/chess_piece_2_black_rook.png");
    blackKnightTexture = LoadPieceTexture("art/chess_piece_2_black_knight.png");
    blackBishopTexture = LoadPieceTexture("art/chess_piece_2_black_bishop.png");
    blackQueenTexture  = LoadPieceTexture("art/chess_piece_2_black_queen.png");
    blackKingTexture   = LoadPieceTexture("art/chess_piece_2_black_king.png");
}

void UnloadGameTextures(void) {
    UnloadTexture(checkerboardTexture);
    UnloadPieceTextures();
}

void UnloadPieceTextures(void) {
    UnloadTexture(whitePawnTexture);
    UnloadTexture(whiteRookTexture);
    UnloadTexture(whiteKnightTexture);
    UnloadTexture(whiteBishopTexture);
    UnloadTexture(whiteQueenTexture);
    UnloadTexture(whiteKingTexture);
    UnloadTexture(blackPawnTexture);
    UnloadTexture(blackRookTexture);
    UnloadTexture(blackKnightTexture);
    UnloadTexture(blackBishopTexture);
    UnloadTexture(blackQueenTexture);
    UnloadTexture(blackKingTexture);
}

void DrawChessboard(void) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Color squareColor = ((row + col) % 2 == 0) ? lightSquareColor : darkSquareColor;
            DrawRectangle(col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, squareColor);
        }
    }
}

void DrawPieces(void) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Texture2D pieceTexture = { 0 };
            switch (board[row][col]) {
                case 1: pieceTexture = whitePawnTexture;   break;
                case 2: pieceTexture = whiteRookTexture;   break;
                case 3: pieceTexture = whiteKnightTexture; break;
                case 4: pieceTexture = whiteBishopTexture; break;
                case 5: pieceTexture = whiteQueenTexture;  break;
                case 6: pieceTexture = whiteKingTexture;   break;
                case 7: pieceTexture = blackPawnTexture;   break;
                case 8: pieceTexture = blackRookTexture;   break;
                case 9: pieceTexture = blackKnightTexture; break;
                case 10: pieceTexture = blackBishopTexture;break;
                case 11: pieceTexture = blackQueenTexture;  break;
                case 12: pieceTexture = blackKingTexture;   break;
                default: continue;
            }
            if (pieceTexture.id != 0) {
                // Calculate the center position of the square
                float x = col * SQUARE_SIZE + (SQUARE_SIZE - pieceTexture.width) / 2.0f;
                float y = row * SQUARE_SIZE + (SQUARE_SIZE - pieceTexture.height) / 2.0f;
                DrawTexture(pieceTexture, x, y, WHITE);
            }
        }
    }
}

void InitializeBoard(void) {
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

Texture2D LoadPieceTexture(const char *filename) {
    Texture2D texture = LoadTexture(filename);
    if (texture.id == 0) {
        fprintf(stderr, "Error: Could not load %s!\n", filename);
        CloseWindow();
        exit(1);
    }
    return texture;
}
