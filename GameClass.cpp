#include "GameClass.h"

#include <math.h>
#include <algorithm>


// Рисование линии между двумя точками
void ShapeRenderer::DrawLine(const Vector2& from, const Vector2& to, uint32_t color) {
    double steps = std::max(abs(to.x - from.x), abs(to.y - from.y));
    if (steps == 0) {
        buffer[int(to.y)][int(to.x)] = color;
        return;
    }
    for (int i = 0; i <= steps; i++) {
        double t = i / steps;
        int x = int(from.x + (to.x - from.x) * t);
        int y = int(from.y + (to.y - from.y) * t);

        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
            buffer[y][x] = color;
        }
    }
}

// Рисование треугольника по трем вершинам
void ShapeRenderer::DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
    DrawLine(p1, p2, color);
    DrawLine(p2, p3, color);
    DrawLine(p3, p1, color);
    FillTriangle(p1, p2, p3, color);
}

// Рисование круга с центром в заданной точке и заданным радиусом
void ShapeRenderer::DrawCircle(const Vector2& center, double radius, uint32_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = int(center.x + x);
                int py = int(center.y + y);
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                    buffer[py][px] = color;
                }
            }
        }
    }
}

// Закрашивание треугольника
void ShapeRenderer::FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
    int minX = int(std::min(p1.x, std::min(p2.x, p3.x)));
    int maxX = int(std::max(p1.x, std::max(p2.x, p3.x)));
    int minY = int(std::min(p1.y, std::min(p2.y, p3.y)));
    int maxY = int(std::max(p1.y, std::max(p2.y, p3.y)));

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (IsPointInTriangle(Vector2(x, y), p1, p2, p3)) {
                if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
                    buffer[y][x] = color;
                }
            }
        }
    }
}

// Проверка точки внутри треугольника 
bool ShapeRenderer::IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3) {
    // Веторное произведение векторов [AB, AC]
    auto cross = [](const Vector2& A, const Vector2& B, const Vector2& C) {
        return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
        };

    double d1 = cross(pt, v1, v2);
    double d2 = cross(pt, v2, v3);
    double d3 = cross(pt, v3, v1);

    bool allPositive = (d1 > 0) && (d2 > 0) && (d3 > 0);
    bool allNegative = (d1 < 0) && (d2 < 0) && (d3 < 0);

    return allPositive || allNegative;
}


// Инициализация ракеты
void Rocket::Initialize() {
    position = Vector2(GameData::START_ROCKET_X, GameData::START_ROCKET_Y);
    direction = Vector2(0, -1);
    velocity = Vector2(0, 0);
    acceleration = Vector2(0, GameData::GRAVITY);
    angle = 0;

    flameSize = 0.0;
    thrust = 0;
}

// Обновление состояния ракеты
void Rocket::Update(double dt) {

    UpdateRotation(dt);
    UpdateThrust(dt);
    ApplyPhysics(dt);

    // Ограничение в пределах экрана
    if (position.x < GameData::WINDOW_MARGIN_X || position.x > SCREEN_WIDTH - GameData::WINDOW_MARGIN_X) {
        velocity.x = 0.0;
        position.x = std::max(GameData::WINDOW_MARGIN_X,
            std::min(position.x, SCREEN_WIDTH - GameData::WINDOW_MARGIN_X));
    }
    if (position.y < GameData::WINDOW_MARGIN_Y || position.y > SCREEN_HEIGHT - GameData::WINDOW_MARGIN_Y) {
        velocity.y = 0.0;
        position.y = std::max(GameData::WINDOW_MARGIN_Y,
            std::min(position.y, SCREEN_HEIGHT - GameData::WINDOW_MARGIN_Y));
    }
}

// Отрисовка ракеты
void Rocket::Draw() {
    DrawRocketBody();
    DrawRocketWindow();
    if (thrust > GameData::THRUST_MIN_VAL) {
        DrawRocketFlame();
    }
}

// Обновление угла поворота ракеты
void Rocket::UpdateRotation(double dt) {
    double rotation = 0.0;

    if (is_key_pressed(VK_LEFT)) {
        rotation = -GameData::ROTATION_SPEED * dt;
    }
    if (is_key_pressed(VK_RIGHT)) {
        rotation = GameData::ROTATION_SPEED * dt;
    }
    angle += rotation;
    // Обновляем вектор направления
    direction.x = sin(angle);
    direction.y = -cos(angle);
}

// Обновление тяги ракеты
void Rocket::UpdateThrust(double dt) {
    int thrustTarget = is_mouse_button_pressed(0) ? 1 : 0;
    thrust += (thrustTarget * GameData::MAX_THRUST - thrust) * GameData::THRUST_SPEED * dt;
    thrust = std::max(0.0, std::min(GameData::MAX_THRUST, thrust));

    // Размер пламени пропорционален тяге
    flameSize = thrust;
}

// Применение физики к ракете
void Rocket::ApplyPhysics(double dt) {
    // Сбрасывание ускорения до гравитации
    acceleration = Vector2(0, GameData::GRAVITY);

    // Добавление ускорения от тяги
    if (thrust > GameData::THRUST_MIN_VAL) {
        Vector2 thrustForce = direction * GameData::MAX_THRUST_FORCE * thrust;
        acceleration = acceleration + thrustForce;
    }
    // Обновление скорости и позиции
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
}

// Отрисовка тела ракеты
void Rocket::DrawRocketBody() {
    Vector2 top = position + direction * (GameData::ROCKET_HEIGHT / 2);

    Vector2 perpendicular(-direction.y, direction.x);
    Vector2 left = position - direction * (GameData::ROCKET_HEIGHT / 2)
        - perpendicular * (GameData::ROCKET_WIDTH / 2);
    Vector2 right = position - direction * (GameData::ROCKET_HEIGHT / 2)
        + perpendicular * (GameData::ROCKET_WIDTH / 2);

    ShapeRenderer::DrawTriangle(top, left, right, GameData::ROCKET_COLOR);
}

// Отрисовка окна ракеты
void Rocket::DrawRocketWindow() {
    Vector2 windowPos = position + direction * GameData::WINDOW_OFFSET_Y;
    ShapeRenderer::DrawCircle(windowPos, GameData::WINDOW_RADIUS, GameData::WINDOW_COLOR);
}

// Отрисовка пламени ракеты
void Rocket::DrawRocketFlame() {
    double flameHeight = GameData::FLAME_MAX_HEIGHT * flameSize;
    double flameWidth = GameData::FLAME_MAX_WIDTH * flameSize;

    // Основание пламени (центр хвоста ракеты)
    Vector2 flameBase = position - direction * (GameData::ROCKET_HEIGHT / 2);

    // Вершина пламени
    Vector2 flameTip = flameBase - direction * flameHeight;

    Vector2 perpendicular(-direction.y, direction.x);
    Vector2 flameLeft = flameBase - perpendicular * (flameWidth / 2);
    Vector2 flameRight = flameBase + perpendicular * (flameWidth / 2);

    ShapeRenderer::DrawTriangle(flameTip, flameLeft, flameRight, GameData::FLAME_COLOR);
}


// Инициализация статических членов Rocket
Vector2 Rocket::position;
Vector2 Rocket::direction;
Vector2 Rocket::velocity;
Vector2 Rocket::acceleration;
double Rocket::angle;
double Rocket::flameSize;
double Rocket::thrust;