#pragma once

#include "Vector2.h"

#include <vector>

// Class Explosion for working with explosion (singleton)
class Explosion {
private:
    static bool isActive;         // Is the explosion active
    static double currentTime;     // Current explosion time
    static Vector2 position;      // Explosion position (center)
    static std::vector<Vector2> positions; // Particle positions
    static std::vector<Vector2> velocities; // Particle velocities

public:
    static bool IsActive() { return isActive; }

    static void Start(const Vector2& pos);
    static void Update(double dt);
    static void Draw();
    static void Finish();
};