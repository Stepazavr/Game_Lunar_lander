#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <vector>


class MoonSurface {
private:
    static std::vector<Vector2> surfacePoints;
    static bool stop_generate;
    static int demonX;

public:
    static void Generate();
	static void Update();
    static void Draw();

    // Проверка коллизии ракеты с поверхностью
    static bool CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir, int& surfaceIndex);

    // Получение высоты ракеты над поверхностью Луны
    static double GetAltitudeAboveMoon(const Vector2& rocketPos);


private:
	static void DrawPart(const Vector2& A, const Vector2& B); // Рисование части поверхности Луны
    static int GetSurfaceIndex(const Vector2& A, const Vector2& B);
    static bool IsPointUnderSurface(const Vector2& point);
    static void GeneratePartOfMauntain(double h_limit, int c); // Генерация части горы (возвышение (c = 1) или спад (c = -1))
    static void GenerateStraightPartOfMauntain();           // Генерация прямого участка горы
    static std::pair<Vector2, Vector2> GetSurfaceUnderRocket(const Vector2& rocketPos);
	static int ChooseDirection(double h_min, double h_max); // 0 (спад) или 1 (возвышение)

    static double Rand_length();
    static double Rand_height();
};