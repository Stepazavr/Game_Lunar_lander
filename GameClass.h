#pragma once

#include "Engine.h"

#include <stdlib.h>
#include <memory.h>


// Класс для хранения всех констант
namespace GameData {
    // Константы экрана
    constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // Стартовая позиция ракеты
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = 0.0;

    // Параметры ракеты
    constexpr double ROCKET_HEIGHT = 40.0;
    constexpr double ROCKET_WIDTH = 30.0;
    constexpr double WINDOW_RADIUS = 5.0;
    constexpr double WINDOW_OFFSET_Y = 0.0;

    // Параметры пламени
    constexpr double FLAME_MAX_HEIGHT = 20.0;
    constexpr double FLAME_MAX_WIDTH = 15.0;

    // Физические параметры
    constexpr double INITIAL_SPEED = 100.0;
    constexpr double GRAVITY = 50.0;
    constexpr double WINDOW_MARGIN_X = 20.0;
    constexpr double WINDOW_MARGIN_Y = 40.0;
    constexpr double ROTATION_SPEED = 3.0;       // Скорость поворота
    constexpr double MAX_THRUST_FORCE = 200.0;   // Максимальная сила тяги
    constexpr double THRUST_MIN_VAL = 0.01;
    constexpr double MAX_THRUST = 1.0;
    constexpr double THRUST_SPEED = 5.0;

    // Цвета
    constexpr uint32_t ROCKET_COLOR = 0xFF0000FF; // Синий
    constexpr uint32_t WINDOW_COLOR = 0xFFFFFFFF; // Белый
    constexpr uint32_t FLAME_COLOR = 0xFFFFA500;  // Оранжевый
};



// 2D Вектор
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


// Класс для отрисовки фигур
class ShapeRenderer {
public:
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


// Класс ракеты (одиночка)
class Rocket {
private:
    static Vector2 position;      // Позиция ракеты
    static Vector2 direction;     // Вектор направления ракеты (от центра к носу)
    static Vector2 velocity;      // Скорость ракеты
    static Vector2 acceleration;  // Ускорение ракеты
    static double angle;          // Текущий угол поворота (рад)
    static double flameSize;      // Размер пламени (0..1)
    static double thrust;         // Сила тяги (0..1)

public:
    static void Initialize(); // Инициализация ракеты

    static void Update(double dt); // Обновление состояния ракеты

    static void Draw(); // Отрисовка ракеты

private:
    Rocket() = delete;

    static void UpdateRotation(double dt); // Обновление угла поворота ракеты
    static void UpdateThrust(double dt); // Обновление тяги ракеты
    static void ApplyPhysics(double dt); // Применение физики к ракете
    static void DrawRocketBody(); // Отрисовка тела ракеты
    static void DrawRocketWindow(); // Отрисовка окна ракеты
    static void DrawRocketFlame(); // Отрисовка пламени ракеты
};
