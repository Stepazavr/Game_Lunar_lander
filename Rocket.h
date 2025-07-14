#pragma once

#include "GameData.h"
#include "Vector2.h"


// Класс ракеты (одиночка)
class Rocket {
private:
    static Vector2 position;      // Позиция ракеты
    static Vector2 direction;     // Вектор направления ракеты (от центра к носу)
    static Vector2 velocity;      // Скорость ракеты
    static Vector2 acceleration;  // Ускорение ракеты
    static double angle;          // Текущий угол поворота (рад)
    static double altitudeAboveMoon;         // Высота ракеты над поверхностью Луны
    static double flameSize;      // Размер пламени (0..1)
    static double thrust;         // Сила тяги (0..1)
    static bool isAlive;
	static double fuel;          // Топливо ракеты
    
public:
    static Vector2 GetVelocity() { return velocity; }
	static Vector2 GetPosition() { return position; }
	static Vector2 GetDirection() { return direction; }
    static double GetAltitude() { return altitudeAboveMoon; }
    static double GetThrust() { return thrust; }
    static double GetAngleDegrees();
    static bool IsAlive() { return isAlive; }
	static double GetFuel() { return fuel; }

public:
    static void Initialize(); // Инициализация ракеты

    static void Update(double dt); // Обновление состояния ракеты

    static void Draw(); // Отрисовка ракеты

	static void Destroy(); // Уничтожение ракеты (взрыв)

private:
    Rocket() = delete;

    static void UpdateRotation(double dt); // Обновление угла поворота ракеты
    static void UpdateThrust(double dt); // Обновление тяги ракеты
    static void ApplyPhysics(double dt); // Применение физики к ракете
    static void DrawRocketBody(); // Отрисовка тела ракеты
    static void DrawRocketWindow(); // Отрисовка окна ракеты
    static void DrawRocketFlame(); // Отрисовка пламени ракеты
};
