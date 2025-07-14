#pragma once

#include <string>

enum Difficulty {
    Easy,    // Легкий уровень
	Medium,  // Средний уровень
    Hard,    // Сложный уровень
	Сount    // Количество уровней сложности
};

class Complexity {
private:
    inline static Difficulty difficulty = Difficulty::Medium;  // Текущий уровень сложности

public:
    // Установить сложность
    static void SetDifficulty(Difficulty newDifficulty) { difficulty = newDifficulty; }

    static void ChangeDifficulty() {
		difficulty = Difficulty((int(difficulty) + 1) % Difficulty::Сount);
	}
    // Получить текущую сложность
	static Difficulty GetDifficulty() { return difficulty; }

    static std::string GetDifficultyName() {
        switch (difficulty) {
            case Difficulty::Easy: return "Easy";
            case Difficulty::Medium: return "Medium";
            case Difficulty::Hard: return "Hard";
            default: return "Unknown";
		}
    }
};