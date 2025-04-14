#include <stdio.h>
#include "raylib.h"
#include "pieces.h"
#include "board.h"
#include "assets.h"
#include "consts.h"

static Piece* floatingPiece = NULL;
static Square* originalSquare = NULL;
static int currentPlayer = WHITE_ID; // Track current turn

// Basic evaluation function for minimax
int EvaluateBoard() {
    int score = 0;
    for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
        Piece* p = GetSquare(i).resident;
        if (p) {
            int value = 0;
            switch (p->id) {
                case PAWN_ID: value = 10; break;
                case KNIGHT_ID: value = 30; break;
                case BISHOP_ID: value = 30; break;
                case ROOK_ID: value = 50; break;
                case QUEEN_ID: value = 90; break;
                case KING_ID: value = 900; break;
            }
            score += (p->side == WHITE_ID ? value : -value);
        }
    }
    return score;
}

// Minimax algorithm
int Minimax(int depth, int isMaximizing) {
    if (depth == 0) return EvaluateBoard();
    int bestScore = isMaximizing ? -9999 : 9999;

    for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
        Square* from = GetSquare(i);
        Piece* p = from->resident;
        if (!p || p->side != (isMaximizing ? BLACK_ID : WHITE_ID)) continue;

        UpdateBoard();

        Node* moves = p->attacking->next;
        while (moves != p->attacking) {
            Square* to = (Square*) moves->data;
            Piece* captured = to->resident;

            to->resident = p;
            from->resident = NULL;

            int score = Minimax(depth - 1, !isMaximizing);
            if (isMaximizing) {
                if (score > bestScore) bestScore = score;
            } else {
                if (score < bestScore) bestScore = score;
            }

            from->resident = p;
            to->resident = captured;
            moves = moves->next;
        }
    }

    return bestScore;
}

// Basic AI move using Minimax
void AIMove() {
    int bestScore = -9999;
    Square* bestFrom = NULL;
    Square* bestTo = NULL;

    for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
        Square* from = GetSquare(i);
        Piece* p = from->resident;
        if (!p || p->side != BLACK_ID) continue;

        UpdateBoard();
        Node* moves = p->attacking->next;
        while (moves != p->attacking) {
            Square* to = (Square*) moves->data;
            Piece* captured = to->resident;

            to->resident = p;
            from->resident = NULL;

            int score = Minimax(2, 0);
            if (score > bestScore) {
                bestScore = score;
                bestFrom = from;
                bestTo = to;
            }

            from->resident = p;
            to->resident = captured;
            moves = moves->next;
        }
    }

    if (bestFrom && bestTo) {
        if (bestTo->resident) DestroyPiece(bestTo->resident);
        bestTo->resident = bestFrom->resident;
        bestFrom->resident = NULL;
        if (bestTo->resident->state == UNMOVED) bestTo->resident->state = MOVED;
    }

    currentPlayer = WHITE_ID;
}

void UpdateInput(void) {
    if (currentPlayer == BLACK_ID) {
        AIMove();
        return;
    }

    Square* sq = GetSquareAt(GetMouseX(), GetMouseY());
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        UpdateBoard();
        if (sq->resident && sq->resident->side == WHITE_ID && !floatingPiece) {
            floatingPiece = sq->resident;
            originalSquare = sq;
            sq->resident = NULL;
        }
    } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        if (originalSquare) {
            if (sq->resident && sq->resident->side == WHITE_ID) {
                originalSquare->resident = floatingPiece;
            } else {
                if (Contains(floatingPiece->attacking, sq)) {
                    DestroyPiece(sq->resident);
                    sq->resident = floatingPiece;
                    if (floatingPiece->state == UNMOVED) {
                        floatingPiece->state = MOVED;
                    }
                    currentPlayer = BLACK_ID;
                } else {
                    originalSquare->resident = floatingPiece;
                }
            }
            originalSquare = NULL;
        }
        floatingPiece = NULL;
    }
}

int main(void) {
    const int screenWidth = SQUARE_SIZE * NUM_COLS;
    const int screenHeight = SQUARE_SIZE * NUM_ROWS;

    InitWindow(screenWidth, screenHeight, "Chess with AI");
    LoadAssets();
    InitBoard();
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        UpdateInput();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawBoard();
        if (floatingPiece) {
            DrawPieceCenter(floatingPiece, GetMouseX(), GetMouseY());
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
