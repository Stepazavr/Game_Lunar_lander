#pragma once

#include "Vector2.h"

#include <vector>



class Explosion {
private:
    static bool isActive;         // Активен ли взрыв
    static double duration;        // Общая продолжительность взрыва
    static double currentTime;     // Текущее время взрыва
    static Vector2 position;      // Позиция взрыва (центр)
    static std::vector<Vector2> particles; // Позиции частиц
    static std::vector<Vector2> velocities; // Скорости частиц

public:
    static void Start(const Vector2& pos);
    static void Update(double dt);
    static void Draw();
    static bool IsActive() { return isActive; }
    static void Finish();
};
