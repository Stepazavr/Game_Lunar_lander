#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <string>



// ����� ��� ��������� �����
class ShapeRenderer {
public:
    // ��������� ������ � ���������
    static void DrawText(int x, int y, const std::string& text, uint32_t color, int scale = 1);

	// ��������� ��������������
	static void DrawRect(int x, int y, int width, int height, uint32_t color);
    
    // ��������� ����� ����� ����� �������
    static void DrawLine(const Vector2& from, const Vector2& to, uint32_t color);

    // ��������� ������������ �� ���� ��������
    static void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);

    // ��������� ����� � ������� � �������� ����� � �������� ��������
    static void DrawCircle(const Vector2& center, double radius, uint32_t color);

private:
    // ������������ ������������
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color);
    // �������� ����� ������ ������������
    static bool IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3);
};
