#pragma once


struct Score {
    inline static int score = 0;

    static void AddScore(int points) {
        score += points;
    }

    static void Reset() {
        score = 0;
    }
};

