// GameConfig.h
#ifndef RAY_CHESS_GAMECONFIG_H
#define RAY_CHESS_GAMECONFIG_H

enum AI_DIFFICULTY {
    EASY,
    MEDIUM,
    HARD
};

enum class PIECE_COLOR {
    C_WHITE,
    C_BLACK
};

class GameConfig {
public:
    static GameConfig& GetInstance() {
        static GameConfig instance;
        return instance;
    }
    
    void SetAIDifficulty(AI_DIFFICULTY difficulty) {
        aiDifficulty = difficulty;
    }
    
    AI_DIFFICULTY GetAIDifficulty() const {
        return aiDifficulty;
    }
    
    int GetAIDepth() const {
        switch (aiDifficulty) {
            case EASY:
                return 2;
            case MEDIUM:
                return 3;
            case HARD:
                return 4;
            default:
                return 3;
        }
    }
    
    void SetPlayerColor(PIECE_COLOR color) {
        playerColor = color;
    }
    
    PIECE_COLOR GetPlayerColor() const {
        return playerColor;
    }
    
    PIECE_COLOR GetAIColor() const {
        return playerColor == PIECE_COLOR::C_WHITE ? PIECE_COLOR::C_BLACK : PIECE_COLOR::C_WHITE;
    }
    
private:
    GameConfig() : aiDifficulty(MEDIUM), playerColor(PIECE_COLOR::C_WHITE) {}
    
    AI_DIFFICULTY aiDifficulty;
    PIECE_COLOR playerColor;
    
    // Singleton: prevent copy construction and assignment
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
};

#endif //RAY_CHESS_GAMECONFIG_H