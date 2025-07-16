#pragma once

#include "Vector2.h"

#include <string>
#include "vector"


// Class for drawing shapes (singleton)
class ShapeRenderer {
public:
	// Drawing a rectangle
	static void DrawRect(int x, int y, int width, int height, uint32_t color);
    
    // Drawing a line between two points
    static void DrawLine(const Vector2& from, const Vector2& to, uint32_t color);

    // Drawing a triangle based on three vertices
    static void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);

    // Drawing a circle with a center and radius
    static void DrawCircle(const Vector2& center, double radius, uint32_t color);

    // Rendering text with scale
    static void DrawText(int x, int y, const std::string& text, uint32_t color, int scale = 1);

    // Creating the triangle
    static std::vector<Vector2> CreateTriangle(const Vector2& pos, const Vector2& dir,
                                               double height, double width);

private:
    // Filling in the triangle
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);
    // Checking the point inside the triangle
    static bool IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3);
};
