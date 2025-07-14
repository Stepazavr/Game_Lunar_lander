#include "HUD.h"
#include "pixel_font.h"
#include "ShapeRenderer.h"
#include "Score.h"
#include "Complexity.h"
#include "Time.h"
#include "GameLogic.h"


#include <sstream>
#include <iomanip>


void HUD::Draw() {
    Vector2 pos = Rocket::GetPosition();
    Vector2 velocity = Rocket::GetVelocity();
	double speed = velocity.Length();
    double angle = Rocket::GetAngleDegrees();
    double altitude = Rocket::GetAltitude();
    double thrust = Rocket::GetThrust();

    // Левый блок (скорости и высота)
    std::vector<std::string> leftText = {
        "Speed X: " + FormatValue(velocity.x * GameData::HUD_VAL_SCALE),
        "Speed Y: " + FormatValue(velocity.y * GameData::HUD_VAL_SCALE),
        "Angle: " + FormatValue(angle) + "°",
        "Altitude: " + FormatValue(altitude * GameData::HUD_VAL_SCALE),
        "Fuel: " + FormatValue(Rocket::GetFuel()) + " L",
        "Thrust: " + FormatValue(thrust * 100) + "%"
    };
    DrawTextBlock(GameData::HUD_PADDING_LEFT_X, GameData::HUD_PADDING_LEFT_Y, leftText);

    // Правый блок (угол и тяга)
    std::vector<std::string> rightText = {
        "Quit game: ESC",
        "Pause: SPACE",
        "Change difficulty: C",
        " ",
        "Score: " + FormatValue(Score::score),
		"High Scores: " + FormatValue(Score::highScores[int(Complexity::GetDifficulty())]),
		"Difficulty: " + Complexity::GetDifficultyName(),
        "Time: " + FormatValue(Time::time) + " s"
    };
    DrawTextBlock(GameData::HUD_PADDING_RIGHT_X, GameData::HUD_PADDING_RIGHT_Y, rightText);

    // Отрисовка индикатора тяги
    DrawBar(GameData::HUD_PADDING_LEFT_X, GameData::HUD_PADDING_RIGHT_Y + leftText.size() * 
        GameData::HUD_FONT_SIZE, GameData::HUD_BAR_WIDTH, GameData::HUD_BAR_HEIGHT, thrust);

    if (GameLogic::isPause) // 930
        HUD::DrawPause(750, GameData::HUD_PADDING_RIGHT_Y + GameData::HUD_FONT_SIZE, 1, GameData::GRAY);

}

std::string HUD::FormatValue(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}



void HUD::DrawTextBlock(int x, int y, const std::vector<std::string>& lines) {
    for (int i = 0; i < lines.size(); ++i) {
        ShapeRenderer::DrawText(x, y + i * GameData::HUD_FONT_SIZE, lines[i], GameData::HUD_TEXT_COLOR, 2);
    }
}


void HUD::DrawBar(int x, int y, int width, int height, float value) {
    ShapeRenderer::DrawRect(x, y, width, height, GameData::HUD_BAR_EMPTY_COLOR); // Серый фон
    ShapeRenderer::DrawRect(x, y, int(width * value), height, GameData::HUD_BAR_COLOR); // Зелёный заполнитель
}

void HUD::DrawPause(int x, int y, int size, uint32_t color) {
    ShapeRenderer::DrawTriangle(Vector2(x, y), Vector2(x + size * 10, y + size * 5),
                                Vector2(x, y + size * 10), color);
}