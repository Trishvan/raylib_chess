#include "pieces.h"
#include "textures.h" // Include textures.h to get the texture declarations
#include "config.h"

void DrawPieces(const int board[BOARD_SIZE][BOARD_SIZE]) {
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