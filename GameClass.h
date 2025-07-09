#pragma once

#include "Engine.h"

#include <stdlib.h>
#include <memory.h>
#include <vector>


// ����� ��� �������� ���� ��������
namespace GameData {
    // ��������� ������
    constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // ��������� ������� ������
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = 40.0;

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

    // ��������� ������ �����������
    //constexpr int MOON_SEGMENTS = 20;          // ���������� ��������� �����������
	//constexpr double MOON_MIN_POINTS_COUNT = 20; // ����������� ���������� ����� �� ����������� ����
	//constexpr double MOON_MAX_POINTS_COUNT = 20; // ������������ ���������� ����� �� ����������� ����
	constexpr double MOON_MIN_STRAIGHT_SEGMENTS_COUNT = 3; // ����������� ���������� ������ ���������
	constexpr double MOON_MAX_STRAIGHT_SEGMENTS_COUNT = 3; // ������������ ���������� ������ ���������
    constexpr double MOON_MIN_HEIGHT_MAP = 100.0;  // ����������� ������ �����������
    constexpr double MOON_MAX_HEIGHT_MAP = 400.0;  // ������������ ������ �����������
	constexpr double MOON_MIN_LENGTH = 10.0; // ����������� ����� ������� �����������
    constexpr double MOON_MAX_LENGTH = 20.0; // ������������ ����� ������� �����������
	constexpr double MOON_MIN_HEIGHT = 5.0; // ����������� ������ ������� �����������
    constexpr double MOON_MAX_HEIGHT = 25.0; // ������������ ������ ������� �����������
	constexpr double MOON_LENGTH_X1 = 60.0; // ����� ������ � ������������� ����� x1
    constexpr double MOON_LENGTH_X2 = 30.0; // ����� ������ � ������������� ����� x2
    constexpr double MOON_LENGTH_X3 = 20.0; // ����� ������ � ������������� ����� x3
    constexpr uint32_t MOON_COLOR = 0xFFFFFFFF; // ����� ���� �����������
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

    double Length() const {
        return sqrt(x * x + y * y);
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
	static double altitudeAboveMoon;         // ������ ������ ��� ������������ ����
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


class MoonSurface {
private:
    static std::vector<Vector2> surfacePoints;
    static bool stop_generate;

public:
    static void Generate();

    static void Draw();

    // �������� �������� ������ � ������������
    static bool CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir);

	// ��������� ������ ������ ��� ������������ ����
    static double GetAltitudeAboveMoon(const Vector2& rocketPos);


private:
    static bool IsPointUnderSurface(const Vector2& point);
    static void GenerateLeftPartOfMauntain(double h_max);   // ��������� ����� ����� ���� (����������)
    static void GenerateRightPartOfMauntain(double h_min);  // ��������� ������ ����� ���� (����)
    static void GenerateStraightPartOfMauntain();           // ��������� ������� ������� ����

    static double Rand_length();
    static double Rand_height();
};