#pragma once

#include "GameData.h"
#include "Vector2.h"



// ����� ��� ��������� �����
class ShapeRenderer {
public:
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
