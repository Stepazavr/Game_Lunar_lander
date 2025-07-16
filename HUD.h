#pragma once

#include "Engine.h"

#include <string>
#include <vector>

// Class HUD for displaying the interface (singleton)
class HUD {
public:
    static void Draw();

private:
	static std::string FormatValue(double value, int precision = 1); // Formatting a value with a given precision
	static void DrawTextBlock(int x, int y, const std::vector<std::string>& lines); // Drawing a block of text
	static void DrawBar(int x, int y, int width, int height, float value); // Drawing a bar with a value (0...1)
	static void DrawPause(int x, int y, int size, uint32_t color); // Drawing a pause icon
};