#pragma once

#include <string>
#include <vector>
#include <cstdint>

// Different difficulties in the game
enum Difficulty {
    Easy,    // Easy level
	Medium,  // Medium level
    Hard,    // Hard level
	Demon,   // Demon level
	Ñount    // Number of difficulty levels
};

// Parameters for each difficulty level
struct DifficultyParams {
    double fuel;
    std::vector<int> pointsCoeff;
    std::string name;
    uint32_t rocketColor;
};

// The Complexity class is responsible for the difficulty in the game (singleton)
class Complexity {
private:
    inline static Difficulty difficulty = Difficulty::Medium;  // Current difficulty level

public:
    static Difficulty GetDifficulty() { return difficulty; }

	// Change the difficulty to the next level
    static void ChangeDifficulty() {
		difficulty = Difficulty((int(difficulty) + 1) % Difficulty::Ñount);
	}
};