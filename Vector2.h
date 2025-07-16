#pragma once

#include <cmath>

// 2D Vector
struct Vector2 {
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