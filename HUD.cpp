#include "HUD.h"
#include "pixel_font.h"
#include "ShapeRenderer.h"

#include <sstream>
#include <iomanip>


void HUD::Draw() {
    Vector2 pos = Rocket::GetPosition();
    Vector2 velocity = Rocket::GetVelocity();
	double speed = velocity.Length();
    double angle = Rocket::GetAngleDegrees();
    double altitude = Rocket::GetAltitude();
    double thrust = Rocket::GetThrust();

    // ����� ���� (�������� � ������)
    std::vector<std::string> leftText = {
        "Speed X: " + FormatValue(velocity.x * GameData::HUD_VAL_SCALE),
        "Speed Y: " + FormatValue(velocity.y * GameData::HUD_VAL_SCALE),
        "Speed: " + FormatValue(speed * GameData::HUD_VAL_SCALE),
        "Altitude: " + FormatValue(altitude * GameData::HUD_VAL_SCALE)
    };
    DrawTextBlock(GameData::HUD_PADDING_LEFT_X, GameData::HUD_PADDING_LEFT_Y, leftText);

    // ������ ���� (���� � ����)
    std::vector<std::string> rightText = {
		"Position X: " + FormatValue(pos.x),
		"Position Y: " + FormatValue(pos.y),
        "Angle: " + FormatValue(angle) + "�",
        "Thrust: " + FormatValue(thrust * 100) + "%",
    };
    DrawTextBlock(GameData::HUD_PADDING_RIGHT_X, GameData::HUD_PADDING_RIGHT_Y, rightText);

    // ��������� ���������� ����
    DrawBar(GameData::HUD_PADDING_RIGHT_X, GameData::HUD_PADDING_RIGHT_Y + rightText.size() * 
        GameData::HUD_FONT_SIZE, GameData::HUD_BAR_WIDTH, GameData::HUD_BAR_HEIGHT, thrust);
}

std::string HUD::FormatValue(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

void HUD::DrawText(int x, int y, const std::string& text, uint32_t color) {
    const auto& font = Fonts::Standard5x7;
    for (char c : text) {
        if (font.characters.count(c)) {
            const auto& bitmap = font.characters.at(c);
            for (int i = 0; i < font.height; ++i) {
                for (int j = 0; j < font.width; ++j) {
                    if (bitmap[i * font.width + j]) {
                        buffer[y + i][x + j] = color;
                    }
                }
            }
        }
        x += font.width + 1; // +1 ������� ����������
    }
}

void HUD::DrawTextScaled(int x, int y, const std::string& text, uint32_t color, int scale) {
    const auto& font = Fonts::Standard5x7;
    for (char c : text) {
        if (font.characters.count(c)) {
            const auto& bitmap = font.characters.at(c);
            for (int i = 0; i < font.height; ++i) {
                for (int j = 0; j < font.width; ++j) {
                    if (bitmap[i * font.width + j]) {
                        // ���������������
                        for (int dy = 0; dy < scale; ++dy) {
                            for (int dx = 0; dx < scale; ++dx) {
                                int px = x + j * scale + dx;
                                int py = y + i * scale + dy;
                                if (px < SCREEN_WIDTH && py < SCREEN_HEIGHT) {
                                    buffer[py][px] = color;
                                }
                            }
                        }
                    }
                }
            }
        }
        x += (font.width + 1) * scale;
    }
}


void HUD::DrawTextBlock(int x, int y, const std::vector<std::string>& lines) {
    for (int i = 0; i < lines.size(); ++i) {
        DrawTextScaled(x, y + i * GameData::HUD_FONT_SIZE, lines[i], GameData::HUD_TEXT_COLOR, 2);
    }
}


void HUD::DrawBar(int x, int y, int width, int height, float value) {
    ShapeRenderer::DrawRect(x, y, width, height, GameData::HUD_BAR_EMPTY_COLOR); // ����� ���
    ShapeRenderer::DrawRect(x, y, int(width * value), height, GameData::HUD_BAR_COLOR); // ������ �����������
}