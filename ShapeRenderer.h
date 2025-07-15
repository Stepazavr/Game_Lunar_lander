#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <string>



// Класс для отрисовки фигур
class ShapeRenderer {
public:
    // Отрисовка текста с масштабом
    static void DrawText(int x, int y, const std::string& text, uint32_t color, int scale = 1);

	// Рисование прямоугольника
	static void DrawRect(int x, int y, int width, int height, uint32_t color);
    
    // Рисование линии между двумя точками
    static void DrawLine(const Vector2& from, const Vector2& to, uint32_t color);

    // Рисование треугольника по трем вершинам
    static void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);

    // Рисование круга с центром в заданной точке и заданным радиусом
    static void DrawCircle(const Vector2& center, double radius, uint32_t color);

private:
    // Закрашивание треугольника
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);
    // Проверка точки внутри треугольника
    static bool IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3);
};
