#include "textures.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

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

Texture2D LoadPieceTexture(const char *filename) {
    Texture2D texture = LoadTexture(filename);
    if (texture.id == 0) {
        fprintf(stderr, "Error: Could not load %s!\n", filename);
        CloseWindow();
        exit(1);
    }
    return texture;
}