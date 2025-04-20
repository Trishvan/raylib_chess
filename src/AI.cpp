// AI.cpp
#include "AI.h"
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

AI::AI(PIECE_COLOR aiColor) : aiColor(aiColor) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

std::pair<Piece*, Move> AI::GetBestMove(Board& board) {
    std::vector<Piece*> pieces = board.GetPiecesByColor(aiColor);
    std::pair<Piece*, Move> bestMove = {nullptr, {}};
    int bestScore = std::numeric_limits<int>::min();
    
    // Map to store all possible moves per piece
    std::map<Piece*, std::vector<Move>> possibleMovesPerPiece;
    
    // Calculate all possible moves for all pieces
    for (Piece* piece : pieces) {
        std::vector<Move> moves = piece->GetPossibleMoves(board);
        
        // Filter moves that lead to check
        for (int i = moves.size() - 1; i >= 0; i--) {
            if (board.MoveLeadsToCheck(piece, moves[i])) {
                moves.erase(moves.begin() + i);
            }
        }
        
        // Special handling for castling
        for (int i = moves.size() - 1; i >= 0; i--) {
            Move& move = moves[i];
            if (move.type == MOVE_TYPE::SHORT_CASTLING || move.type == MOVE_TYPE::LONG_CASTLING) {
                std::vector<Position> intermediaryPositions;
                
                if (move.type == MOVE_TYPE::SHORT_CASTLING) {
                    intermediaryPositions = {{piece->GetPosition().i, 5}, {piece->GetPosition().i, 6}};
                } else {
                    intermediaryPositions = {{piece->GetPosition().i, 3}, {piece->GetPosition().i, 2}};
                }
                
                for (const Position& position : intermediaryPositions) {
                    if (board.MoveLeadsToCheck(piece, {MOVE_TYPE::WALK, position})) {
                        moves.erase(moves.begin() + i);
                        break;
                    }
                }
            }
        }
        
        if (!moves.empty()) {
            possibleMovesPerPiece[piece] = moves;
        }
    }
    
    // If no legal moves, return nullptr (checkmate or stalemate)
    if (possibleMovesPerPiece.empty()) {
        return bestMove;
    }
    
    // Evaluate each move using minimax
    for (const auto& [piece, moves] : possibleMovesPerPiece) {
        for (const Move& move : moves) {
            // Create a copy of the board
            Board boardCopy = board;
            Piece* pieceCopy = boardCopy.At(piece->GetPosition());
            
            // Make the move on the copied board
            boardCopy.DoMove(pieceCopy, move);
            
            // Evaluate the position using minimax
            int score = Minimax(boardCopy, MAX_DEPTH - 1, 
                               std::numeric_limits<int>::min(), 
                               std::numeric_limits<int>::max(), 
                               false);
            
            // If this move has a better score, update the best move
            if (score > bestScore) {
                bestScore = score;
                bestMove = {piece, move};
            }
        }
    }
    
    // If multiple moves have the same score, we could add some randomness
    // to avoid predictable play (not implemented here)
    
    return bestMove;
}

int AI::Minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing) {
    // Base case: reached depth limit or game ended
    if (depth == 0) {
        return EvaluateBoard(board);
    }
    
    PIECE_COLOR currentColor = isMaximizing ? aiColor : Piece::GetInverseColor(aiColor);
    std::vector<Piece*> pieces = board.GetPiecesByColor(currentColor);
    
    if (isMaximizing) {
        int maxEval = std::numeric_limits<int>::min();
        
        // For each piece of the current player
        for (Piece* piece : pieces) {
            std::vector<Move> moves = piece->GetPossibleMoves(board);
            
            // Filter invalid moves
            for (int i = moves.size() - 1; i >= 0; i--) {
                if (board.MoveLeadsToCheck(piece, moves[i])) {
                    moves.erase(moves.begin() + i);
                }
            }
            
            // For each valid move
            for (const Move& move : moves) {
                // Create a copy of the board
                Board boardCopy = board;
                Piece* pieceCopy = boardCopy.At(piece->GetPosition());
                
                // Make the move
                boardCopy.DoMove(pieceCopy, move);
                
                // Recursive evaluation
                int eval = Minimax(boardCopy, depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                
                // Alpha-beta pruning
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
            
            // Early cutoff
            if (beta <= alpha) {
                break;
            }
        }
        
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        
        // For each piece of the opponent
        for (Piece* piece : pieces) {
            std::vector<Move> moves = piece->GetPossibleMoves(board);
            
            // Filter invalid moves
            for (int i = moves.size() - 1; i >= 0; i--) {
                if (board.MoveLeadsToCheck(piece, moves[i])) {
                    moves.erase(moves.begin() + i);
                }
            }
            
            // For each valid move
            for (const Move& move : moves) {
                // Create a copy of the board
                Board boardCopy = board;
                Piece* pieceCopy = boardCopy.At(piece->GetPosition());
                
                // Make the move
                boardCopy.DoMove(pieceCopy, move);
                
                // Recursive evaluation
                int eval = Minimax(boardCopy, depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                
                // Alpha-beta pruning
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
            
            // Early cutoff
            if (beta <= alpha) {
                break;
            }
        }
        
        return minEval;
    }
}

int AI::EvaluateBoard(const Board& board) {
    int score = 0;
    
    // Get all pieces
    std::vector<Piece*> aiPieces = board.GetPiecesByColor(aiColor);
    std::vector<Piece*> opponentPieces = board.GetPiecesByColor(Piece::GetInverseColor(aiColor));
    
    // Calculate material and positional advantage for AI pieces
    for (Piece* piece : aiPieces) {
        score += GetPieceValue(piece->type);
        score += GetPositionalScore(piece);
    }
    
    // Calculate material and positional advantage for opponent pieces (subtract)
    for (Piece* piece : opponentPieces) {
        score -= GetPieceValue(piece->type);
        score -= GetPositionalScore(piece);
    }
    
    // Check for check/checkmate situations
    if (board.IsInCheck(Piece::GetInverseColor(aiColor))) {
        score += 50; // Bonus for putting opponent in check
    }
    
    if (board.IsInCheck(aiColor)) {
        score -= 50; // Penalty for being in check
    }
    
    return score;
}

int AI::GetPieceValue(PIECE_TYPE type) const {
    switch (type) {
        case PIECE_TYPE::PEON:
            return 100;
        case PIECE_TYPE::KNIGHT:
            return 320;
        case PIECE_TYPE::BISHOP:
            return 330;
        case PIECE_TYPE::ROOK:
            return 500;
        case PIECE_TYPE::QUEEN:
            return 900;
        case PIECE_TYPE::KING:
            return 20000; // Very high value to prioritize king safety
        default:
            return 0;
    }
}

int AI::GetPositionalScore(Piece* piece) const {
    Position pos = piece->GetPosition();
    int row = pos.i;
    int col = pos.j;
    
    // For black pieces, mirror the table vertically
    if (piece->color == PIECE_COLOR::C_BLACK) {
        row = 7 - row;
    }
    
    switch (piece->type) {
        case PIECE_TYPE::PEON:
            return pawnTable[row][col];
        case PIECE_TYPE::KNIGHT:
            return knightTable[row][col];
        case PIECE_TYPE::BISHOP:
            return bishopTable[row][col];
        case PIECE_TYPE::ROOK:
            return rookTable[row][col];
        case PIECE_TYPE::QUEEN:
            return queenTable[row][col];
        case PIECE_TYPE::KING:
            return kingTableMiddlegame[row][col];
        default:
            return 0;
    }
}