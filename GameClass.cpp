#include "GameClass.h"

#include <math.h>
#include <algorithm>
#include <iostream>


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
    altitudeAboveMoon = SCREEN_HEIGHT;

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
	altitudeAboveMoon = MoonSurface::GetAltitudeAboveMoon(position - direction * (GameData::ROCKET_HEIGHT / 2));

    // Коллизия с поверхностью
    if (MoonSurface::CheckCollision(position, direction)) {
        if (altitudeAboveMoon < 1.0 && std::abs(angle) < 1.0) {
            //std::cout << "Rocket landed successfully!" << std::endl;
        } else {
            //std::cout << "Rocket crashed!" << std::endl;
			//schedule_quit_game();
        }
        velocity = Vector2(0, 0);
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


void MoonSurface::Generate() {
    surfacePoints.clear();

    // Первая точка
    double x = 0;
    double y = SCREEN_HEIGHT - (GameData::MOON_MIN_HEIGHT_MAP + 1 +
        rand() % int(GameData::MOON_MAX_HEIGHT_MAP - GameData::MOON_MIN_HEIGHT_MAP));
    surfacePoints.emplace_back(x, y);

    while (!stop_generate) {
        double h = SCREEN_HEIGHT - surfacePoints.back().y;
        double h_max = h + rand() % int(GameData::MOON_MAX_HEIGHT_MAP - h);
        double h_min = GameData::MOON_MIN_HEIGHT_MAP + rand() %
            int(h_max - GameData::MOON_MIN_HEIGHT_MAP);

        GenerateLeftPartOfMauntain(h_max);
        GenerateStraightPartOfMauntain();
        GenerateRightPartOfMauntain(h_min);
        GenerateStraightPartOfMauntain();
    }
}

// Генерация длины участка поверхности
double MoonSurface::Rand_length() {
    double length = GameData::MOON_MIN_LENGTH;
    if (GameData::MOON_MIN_LENGTH != GameData::MOON_MAX_LENGTH) {
        length += rand() % int(GameData::MOON_MAX_LENGTH - GameData::MOON_MIN_LENGTH);
    }
    return length;
}

// Генерация высоты участка поверхности
double MoonSurface::Rand_height() {
    double height = GameData::MOON_MIN_HEIGHT;
    if (GameData::MOON_MIN_HEIGHT != GameData::MOON_MAX_HEIGHT) {
        height += rand() % int(GameData::MOON_MAX_HEIGHT - GameData::MOON_MIN_HEIGHT);
    }
    return height;
}

// Генерация левой части горы (возвышение)
void MoonSurface::GenerateLeftPartOfMauntain(double h_max) {
    if (stop_generate) return;
    bool go_up = true;
    while (go_up) {
        double x = surfacePoints.back().x + Rand_length();
        double h = SCREEN_HEIGHT - surfacePoints.back().y + Rand_height();
        if (h >= h_max) {
            h = h_max;
            go_up = false;
        }
        double y = SCREEN_HEIGHT - h;
        if (x >= SCREEN_WIDTH) {
            x = SCREEN_WIDTH;
            stop_generate = true;
        }
        surfacePoints.emplace_back(x, y);
        if (stop_generate) return;
    }
}

// Генерация правой части горы (спад)
void MoonSurface::GenerateRightPartOfMauntain(double h_min) {
    if (stop_generate) return;
    bool go_down = true;
    while (go_down) {
        double x = surfacePoints.back().x + Rand_length();
        double h = SCREEN_HEIGHT - surfacePoints.back().y - Rand_height();
        if (h <= h_min) {
            h = h_min;
            go_down = false;
        }
        double y = SCREEN_HEIGHT - h;
        if (x >= SCREEN_WIDTH) {
            x = SCREEN_WIDTH;
            stop_generate = true;
        }
        surfacePoints.emplace_back(x, y);
        if (stop_generate) break;
    }
}

// Генерация прямого участка горы
void MoonSurface::GenerateStraightPartOfMauntain() {
    if (stop_generate) return;
    double x = surfacePoints.back().x + GameData::MOON_LENGTH_X1;
    double y = surfacePoints.back().y;
    if (x >= SCREEN_WIDTH) {
        x = SCREEN_WIDTH;
        stop_generate = true;
    }
    surfacePoints.emplace_back(x, y);
}


// Рисование поверхности Луны
void MoonSurface::Draw() {
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        ShapeRenderer::DrawLine(surfacePoints[i - 1], surfacePoints[i], GameData::MOON_COLOR);
    }
}

// Проверка коллизии ракеты с поверхностью
bool MoonSurface::CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir){
    // 1. Получаем три вершины ракеты (нос, левый и правый угол)
    Vector2 nose = rocketPos + rocketDir * (GameData::ROCKET_HEIGHT / 2);
    Vector2 left = rocketPos - rocketDir * (GameData::ROCKET_HEIGHT / 2) +
        Vector2(-rocketDir.y, rocketDir.x) * (GameData::ROCKET_WIDTH / 2);
    Vector2 right = rocketPos - rocketDir * (GameData::ROCKET_HEIGHT / 2) +
        Vector2(-rocketDir.y, rocketDir.x) * (-GameData::ROCKET_WIDTH / 2);

    // 2. Проверяем каждую точку ракеты на пересечение с поверхностью
    return IsPointUnderSurface(nose) ||
        IsPointUnderSurface(left) ||
        IsPointUnderSurface(right);
}

// Вспомогательная функция: проверяет, находится ли точка под поверхностью
bool MoonSurface::IsPointUnderSurface(const Vector2& point){
    return GetAltitudeAboveMoon(point) <= 0;
}

// Получение высоты ракеты над поверхностью Луны
double MoonSurface::GetAltitudeAboveMoon(const Vector2& rocketPos) {
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        if (rocketPos.x >= surfacePoints[i - 1].x && rocketPos.x <= surfacePoints[i].x) {
            double t = (rocketPos.x - surfacePoints[i - 1].x) / (surfacePoints[i].x - surfacePoints[i - 1].x);
            double surfaceY = surfacePoints[i - 1].y + t * (surfacePoints[i].y - surfacePoints[i - 1].y);
            return surfaceY - rocketPos.y; // Высота над поверхностью
        }
    }
    return SCREEN_HEIGHT;
}


// Инициализация статических членов Rocket
Vector2 Rocket::position;
Vector2 Rocket::direction;
Vector2 Rocket::velocity;
Vector2 Rocket::acceleration;
double Rocket::angle;
double Rocket::altitudeAboveMoon;
double Rocket::flameSize;
double Rocket::thrust;

// Инициализация статических членов MoonSurface
std::vector<Vector2> MoonSurface::surfacePoints;
bool MoonSurface::stop_generate = false;