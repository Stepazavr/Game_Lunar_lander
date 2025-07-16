#include "ShapeRenderer.h"
#include "PixelFont.h"
#include "Engine.h"
#include "GameData.h"

#include <algorithm>

// Creating the triangle
std::vector<Vector2> ShapeRenderer::CreateTriangle(const Vector2& pos, const Vector2& dir, 
                                                   double height, double width) {
    std::vector<Vector2> triangle(3);
    Vector2 perpendicular(-dir.y, dir.x);
    triangle[0] = pos + dir * (height / 2);
    triangle[1] = pos - dir * (height / 2) - perpendicular * (width / 2);
    triangle[2] = pos - dir * (height / 2) + perpendicular * (width / 2);
    return triangle;
}

// Drawing a rectangle
void ShapeRenderer::DrawRect(int x, int y, int width, int height, uint32_t color) {
    for (int i = y; i < y + height; i++)
        for (int j = x; j < x + width; j++)
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH)
                buffer[i][j] = color;
}

// Drawing a line between two points
void ShapeRenderer::DrawLine(const Vector2& from, const Vector2& to, uint32_t color) {
    double steps = std::max(abs(to.x - from.x), abs(to.y - from.y));
    if (steps == 0) {
        buffer[int(to.y)][int(to.x)] = color;
        return;
    }
    for (int i = 0; i <= steps; i++) {
        double t = i / steps;
        int x = int(from.x + (to.x - from.x) * t);
        int y = int(from.y + (to.y - from.y) * t);

        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
            buffer[y][x] = color;
    }
}

// Drawing a triangle based on three vertices
void ShapeRenderer::DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
    DrawLine(p1, p2, color);
    DrawLine(p2, p3, color);
    DrawLine(p3, p1, color);
    FillTriangle(p1, p2, p3, color);
}

// Drawing a circle with a center and radius
void ShapeRenderer::DrawCircle(const Vector2& center, double radius, uint32_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = int(center.x) + x;
                int py = int(center.y) + y;
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT)
                    buffer[py][px] = color;
            }
        }
    }
}

// Rendering text with scale
void ShapeRenderer::DrawText(int x, int y, const std::string& text, uint32_t color, int scale) {
    const auto& font = Fonts::Standard5x7;
    for (char c : text) {
        if (font.characters.count(c)) {
            const auto& bitmap = font.characters.at(c);
            for (int i = 0; i < font.height; i++) {
                for (int j = 0; j < font.width; j++) {
                    if (bitmap[i * font.width + j]) {
                        // Scaling
                        for (int dy = 0; dy < scale; dy++) {
                            for (int dx = 0; dx < scale; dx++) {
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
        x += (font.width + GameData::HUD_MARGIN_X) * scale;
    }
}

// Filling in the triangle
void ShapeRenderer::FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
    int minX = int(std::min(p1.x, std::min(p2.x, p3.x)));
    int maxX = int(std::max(p1.x, std::max(p2.x, p3.x)));
    int minY = int(std::min(p1.y, std::min(p2.y, p3.y)));
    int maxY = int(std::max(p1.y, std::max(p2.y, p3.y)));

    for (int y = minY; y <= maxY; y++)
        for (int x = minX; x <= maxX; x++)
            if (IsPointInTriangle(Vector2(x, y), p1, p2, p3)) {
                if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
                    buffer[y][x] = color;
            }
}

// Checking the point inside the triangle
bool ShapeRenderer::IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3) {
    // Vector product of vectors [AB, AC]
    auto cross = [](const Vector2& A, const Vector2& B, const Vector2& C) {
        return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
        };

    double d1 = cross(pt, v1, v2);
    double d2 = cross(pt, v2, v3);
    double d3 = cross(pt, v3, v1);

    bool allPositive = (d1 > 0) && (d2 > 0) && (d3 > 0);
    bool allNegative = (d1 < 0) && (d2 < 0) && (d3 < 0);

    return allPositive || allNegative;
}