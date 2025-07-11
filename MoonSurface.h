#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <vector>


class MoonSurface {
private:
    static std::vector<Vector2> surfacePoints;
    static bool stop_generate;

public:
    static void Generate();

    static void Draw();

    // Проверка коллизии ракеты с поверхностью
    static bool CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir);

    // Получение высоты ракеты над поверхностью Луны
    static double GetAltitudeAboveMoon(const Vector2& rocketPos);


private:
    static bool IsPointUnderSurface(const Vector2& point);
    static void GenerateLeftPartOfMauntain(double h_max);   // Генерация левой части горы (возвышение)
    static void GenerateRightPartOfMauntain(double h_min);  // Генерация правой части горы (спад)
    static void GenerateStraightPartOfMauntain();           // Генерация прямого участка горы

    static double Rand_length();
    static double Rand_height();
};