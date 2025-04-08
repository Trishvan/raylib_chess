#ifndef TEXTURES_H
#define TEXTURES_H

#include "raylib.h"


// --- Global Variables ---
extern Texture2D checkerboardTexture;
extern Color lightSquareColor;
extern Color darkSquareColor;

// Piece textures
extern Texture2D whitePawnTexture;
extern Texture2D whiteRookTexture;
extern Texture2D whiteKnightTexture;
extern Texture2D whiteBishopTexture;
extern Texture2D whiteQueenTexture;
extern Texture2D whiteKingTexture;
extern Texture2D blackPawnTexture;
extern Texture2D blackRookTexture;
extern Texture2D blackKnightTexture;
extern Texture2D blackBishopTexture;
extern Texture2D blackQueenTexture;
extern Texture2D blackKingTexture;

// --- Function Declarations ---
void LoadGameTextures(void);
void UnloadGameTextures(void);
void UnloadPieceTextures(void);
Texture2D LoadPieceTexture(const char *filename);

#endif