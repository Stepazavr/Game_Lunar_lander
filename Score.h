#pragma once

#include "Complexity.h"

#include <vector>


// The Score class is responsible for managing the points scored in the game. (singleton)
struct Score {
	inline static int score = 0; // Current score
    inline static std::vector<int> highScores =
        std::vector<int>(static_cast<int>(Difficulty::Ñount), 0); // High scores (Easy, Medium, Hard, Demon)


    static void AddScore(int points) {
        score += points;
		highScores[int(Complexity::GetDifficulty())] = 
            std::max(highScores[int(Complexity::GetDifficulty())], score); // Update the high score
    }

    static void Reset() {
        score = 0;
    }
};