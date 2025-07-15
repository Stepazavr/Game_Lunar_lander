#pragma once

#include "Engine.h"

#include <string>
#include <vector>


class HUD {
public:
    static void Draw();

private:
    static std::string FormatValue(double value, int precision = 1);
    static void DrawTextBlock(int x, int y, const std::vector<std::string>& lines);
    static void DrawBar(int x, int y, int width, int height, float value);
    static void DrawPause(int x, int y, int size, uint32_t color);
};