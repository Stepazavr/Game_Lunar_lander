#pragma once

#include <string>

enum Difficulty {
    Easy,    // ������ �������
	Medium,  // ������� �������
    Hard,    // ������� �������
	Demon,   // �����
	�ount    // ���������� ������� ���������
};

class Complexity {
private:
    inline static Difficulty difficulty = Difficulty::Easy;  // ������� ������� ���������

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
			case Difficulty::Demon: return "DEMON";
            default: return "Unknown";
		}
    }
};