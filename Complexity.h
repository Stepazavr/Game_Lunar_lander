#pragma once

#include <string>

enum Difficulty {
    Easy,    // ������ �������
	Medium,  // ������� �������
    Hard,    // ������� �������
	�ount    // ���������� ������� ���������
};

class Complexity {
private:
    inline static Difficulty difficulty = Difficulty::Medium;  // ������� ������� ���������

public:
    // ���������� ���������
    static void SetDifficulty(Difficulty newDifficulty) { difficulty = newDifficulty; }

    static void ChangeDifficulty() {
		difficulty = Difficulty((int(difficulty) + 1) % Difficulty::�ount);
	}
    // �������� ������� ���������
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