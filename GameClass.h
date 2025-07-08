#pragma once

#include "Engine.h"

#include <stdlib.h>
#include <memory.h>


// ����� ��� �������� ���� ��������
namespace GameData {
    // ��������� ������
    constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // ��������� ������� ������
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = 0.0;

    // ��������� ������
    constexpr double ROCKET_HEIGHT = 40.0;
    constexpr double ROCKET_WIDTH = 30.0;
    constexpr double WINDOW_RADIUS = 5.0;
    constexpr double WINDOW_OFFSET_Y = 0.0;

    // ��������� �������
    constexpr double FLAME_MAX_HEIGHT = 20.0;
    constexpr double FLAME_MAX_WIDTH = 15.0;

    // ���������� ���������
    constexpr double INITIAL_SPEED = 100.0;
    constexpr double GRAVITY = 50.0;
    constexpr double WINDOW_MARGIN_X = 20.0;
    constexpr double WINDOW_MARGIN_Y = 40.0;
    constexpr double ROTATION_SPEED = 3.0;       // �������� ��������
    constexpr double MAX_THRUST_FORCE = 200.0;   // ������������ ���� ����
    constexpr double THRUST_MIN_VAL = 0.01;
    constexpr double MAX_THRUST = 1.0;
    constexpr double THRUST_SPEED = 5.0;

    // �����
    constexpr uint32_t ROCKET_COLOR = 0xFF0000FF; // �����
    constexpr uint32_t WINDOW_COLOR = 0xFFFFFFFF; // �����
    constexpr uint32_t FLAME_COLOR = 0xFFFFA500;  // ���������
};



// 2D ������
class Vector2 {
public:
    double x, y;

    Vector2(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}

    Vector2 operator+(const Vector2& a) const {
        return Vector2(x + a.x, y + a.y);
    }
    Vector2 operator-(const Vector2& a) const {
        return Vector2(x - a.x, y - a.y);
    }
    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};


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


// ����� ������ (��������)
class Rocket {
private:
    static Vector2 position;      // ������� ������
    static Vector2 direction;     // ������ ����������� ������ (�� ������ � ����)
    static Vector2 velocity;      // �������� ������
    static Vector2 acceleration;  // ��������� ������
    static double angle;          // ������� ���� �������� (���)
    static double flameSize;      // ������ ������� (0..1)
    static double thrust;         // ���� ���� (0..1)

public:
    static void Initialize(); // ������������� ������

    static void Update(double dt); // ���������� ��������� ������

    static void Draw(); // ��������� ������

private:
    Rocket() = delete;

    static void UpdateRotation(double dt); // ���������� ���� �������� ������
    static void UpdateThrust(double dt); // ���������� ���� ������
    static void ApplyPhysics(double dt); // ���������� ������ � ������
    static void DrawRocketBody(); // ��������� ���� ������
    static void DrawRocketWindow(); // ��������� ���� ������
    static void DrawRocketFlame(); // ��������� ������� ������
};
