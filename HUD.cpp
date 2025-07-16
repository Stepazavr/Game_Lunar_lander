#include "HUD.h"
#include "ShapeRenderer.h"
#include "Score.h"
#include "Complexity.h"
#include "Time.h"
#include "GameLogic.h"
#include "Rocket.h"
#include "GameData.h"

#include <sstream>
#include <iomanip>


void HUD::Draw() {
    // Left block (rocket parameters)
    std::vector<std::string> leftText = {
        "Speed X: " + FormatValue(Rocket::GetVelocity().x * GameData::HUD_VAL_SCALE),
        "Speed Y: " + FormatValue(Rocket::GetVelocity().y * GameData::HUD_VAL_SCALE),
        "Angle: " + FormatValue(Rocket::GetAngleDegrees()) + "°",
        "Altitude: " + FormatValue(Rocket::GetAltitude() * GameData::HUD_VAL_SCALE),
        "Fuel: " + FormatValue(Rocket::GetFuel()) + " L",
		"Thrust: " + FormatValue(Rocket::GetThrust() * 100) + "%" // percentage
    };
    DrawTextBlock(GameData::HUD_PADDING_LEFT_X, GameData::HUD_PADDING_LEFT_Y, leftText);

    // Right block (interface hints, points, difficulty, and time)
    std::vector<std::string> rightText = {
        "Quit game: ESC",
        "Pause: SPACE",
        "Change difficulty: C",
        " ",
        "Score: " + FormatValue(Score::score),
		"High Scores: " + FormatValue(Score::highScores[int(Complexity::GetDifficulty())]),
		"Difficulty: " + GameData::DIFFICULTY_CONFIG.at(Complexity::GetDifficulty()).name,
        "Time: " + FormatValue(Time::time) + " s"
    };
    DrawTextBlock(GameData::HUD_PADDING_RIGHT_X, GameData::HUD_PADDING_RIGHT_Y, rightText);

    // Drawing a thrust bar
    DrawBar(GameData::HUD_PADDING_LEFT_X, GameData::HUD_PADDING_RIGHT_Y + leftText.size() * 
        GameData::HUD_MARGIN_Y, GameData::HUD_BAR_WIDTH, GameData::HUD_BAR_HEIGHT, Rocket::GetThrust());

    // Drawing a pause icon
    if (GameLogic::isPause)
        HUD::DrawPause(GameData::HUD_PAUSE_ICON_POSITION, GameData::HUD_PADDING_RIGHT_Y + GameData::HUD_MARGIN_Y,
                       GameData::HUD_PAUSE_ICON_SIZE, GameData::HUD_PAUSE_ICON_COLOR);
}

// Formatting a value with a given precision
std::string HUD::FormatValue(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

// Drawing a block of text
void HUD::DrawTextBlock(int x, int y, const std::vector<std::string>& lines) {
    for (int i = 0; i < lines.size(); i++) {
        ShapeRenderer::DrawText(x, y + i * GameData::HUD_MARGIN_Y, lines[i],
                                GameData::HUD_TEXT_COLOR, GameData::HUD_SCALE_COMMON);
    }
}

// Drawing a bar with a value (0...1)
void HUD::DrawBar(int x, int y, int width, int height, float value) {
    ShapeRenderer::DrawRect(x, y, width, height, GameData::HUD_BAR_EMPTY_COLOR); // background
    ShapeRenderer::DrawRect(x, y, int(width * value), height, GameData::HUD_BAR_COLOR); // filling
}

// Drawing a pause icon
void HUD::DrawPause(int x, int y, int size, uint32_t color) {
    ShapeRenderer::DrawTriangle(Vector2(x, y), Vector2(x + size, y + size / 2),
                                Vector2(x, y + size), color);
}