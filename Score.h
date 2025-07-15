#pragma once

#include "Complexity.h"

#include <vector>

struct Score {
	inline static int score = 0; // Current score
	inline static std::vector<int> highScores = { 0, 0, 0, 0 }; // High scores (Easy, Medium, Hard, Demon)

    static void AddScore(int points) {
        score += points;
		highScores[int(Complexity::GetDifficulty())] = std::max(highScores[int(Complexity::GetDifficulty())], score);
    }

    static void Reset() {
        score = 0;
    }
};