#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <algorithm>

// Класс для хранения всех констант
class GameData {
public:
    // Константы экрана
    static constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    static constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // Стартовая позиция ракеты
    static constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    static constexpr double START_ROCKET_Y = 0.0;

    // Параметры ракеты
    static constexpr double ROCKET_HEIGHT = 40.0;
    static constexpr double ROCKET_WIDTH = 30.0;
    static constexpr double WINDOW_RADIUS = 5.0;
    static constexpr double WINDOW_OFFSET_Y = 0.0;

    // Параметры пламени
    static constexpr double FLAME_MIN_SIZE = 0.01;
    static constexpr double FLAME_MAX_HEIGHT = 20.0;
    static constexpr double FLAME_MAX_WIDTH = 15.0;

    // Физические параметры
    static constexpr double INITIAL_SPEED = 100.0;
    static constexpr double FLAME_SPEED = 10.0;
    static constexpr double GRAVITY = 50.0;
    static constexpr double WINDOW_MARGIN_X = 20.0;
    static constexpr double WINDOW_MARGIN_Y = 40.0;

    // Цвета
    static constexpr uint32_t ROCKET_COLOR = 0xFF0000FF; // Синий
    static constexpr uint32_t WINDOW_COLOR = 0xFFFFFFFF; // Белый
    static constexpr uint32_t FLAME_COLOR = 0xFFFFA500;  // Оранжевый
};

// 2D Вектор
class Vector2 {
public:
    double x, y;

    Vector2(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};

// Класс для отрисовки фигур
class ShapeRenderer {
public:
	// Рисует линию между двумя точками
    static void DrawLine(const Vector2& from, const Vector2& to, uint32_t color) {
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
	// Рисует треугольник, соединяя три точки и заполняя его цветом
    static void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
        DrawLine(p1, p2, color);
        DrawLine(p2, p3, color);
        DrawLine(p3, p1, color);
        FillTriangle(p1, p2, p3, color);
    }
	// Рисует круг с центром в заданной точке и заданным радиусом
    static void DrawCircle(const Vector2& center, double radius, uint32_t color) {
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

private:
	// Заполняет треугольник цветом
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, uint32_t color) {
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
	// Проверяет, находится ли точка внутри треугольника    
    static bool IsPointInTriangle(const Vector2& pt, const Vector2& v1, const Vector2& v2, const Vector2& v3) {
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
};

// Класс ракеты (одиночка)
class Rocket {
private:
    Rocket() = delete;

    static Vector2 position;
    static Vector2 velocity;
    static Vector2 acceleration;
    static double flameSize;
    static int flameTarget;

public:
    static void Initialize() {
        position = Vector2(GameData::START_ROCKET_X, GameData::START_ROCKET_Y);
        velocity = Vector2(0, 0);
        acceleration = Vector2(0, GameData::GRAVITY);
        flameSize = 0.0;
        flameTarget = 0;
    }

    static void Update(double dt) {
        velocity = velocity + acceleration * dt;

        // Обработка управления
        if (is_key_pressed(VK_LEFT))  velocity.x = -GameData::INITIAL_SPEED;
        if (is_key_pressed(VK_RIGHT)) velocity.x = GameData::INITIAL_SPEED;
        if (is_key_pressed(VK_UP))    velocity.y = -GameData::INITIAL_SPEED;
        if (is_key_pressed(VK_DOWN))  velocity.y = GameData::INITIAL_SPEED;

        // Обновляем позицию
        position = position + velocity * dt;

        // Ограничение в пределах экрана
        position.x = std::max(GameData::WINDOW_MARGIN_X,
            std::min(position.x, SCREEN_WIDTH - GameData::WINDOW_MARGIN_X));
        position.y = std::max(GameData::WINDOW_MARGIN_Y,
            std::min(position.y, SCREEN_HEIGHT - GameData::WINDOW_MARGIN_Y));

        // Управление пламенем
        bool isMoving = is_key_pressed(VK_LEFT) || is_key_pressed(VK_RIGHT) ||
            is_key_pressed(VK_UP) || is_key_pressed(VK_DOWN);

        flameTarget = isMoving ? 1 : 0;
        flameSize += (flameTarget - flameSize) * GameData::FLAME_SPEED * dt;
        flameSize = fmax(0.0, fmin(1.0, flameSize));
    }
	// Отрисовка ракеты
    static void Draw() {
        DrawRocketBody();
        DrawRocketWindow();
        DrawRocketFlame();
    }

private:
	// Отрисовка корпуса ракеты
    static void DrawRocketBody() {
        Vector2 top(position.x, position.y - GameData::ROCKET_HEIGHT / 2);
        Vector2 left(position.x - GameData::ROCKET_WIDTH / 2, position.y + GameData::ROCKET_HEIGHT / 2);
        Vector2 right(position.x + GameData::ROCKET_WIDTH / 2, position.y + GameData::ROCKET_HEIGHT / 2);
        ShapeRenderer::DrawTriangle(top, left, right, GameData::ROCKET_COLOR);
    }
    // Отрисовка иллюминатора
    static void DrawRocketWindow() {
        Vector2 windowPos(position.x, position.y + GameData::WINDOW_OFFSET_Y);
        ShapeRenderer::DrawCircle(windowPos, GameData::WINDOW_RADIUS, GameData::WINDOW_COLOR);
    }
	// Отрисовка пламени ракеты
    static void DrawRocketFlame() {
        if (flameSize > GameData::FLAME_MIN_SIZE) {
            double flameHeight = GameData::FLAME_MAX_HEIGHT * flameSize;
            double flameWidth = GameData::FLAME_MAX_WIDTH * flameSize;

            Vector2 flameTop(position.x, position.y + GameData::ROCKET_HEIGHT / 2 + flameHeight);
            Vector2 flameLeft(position.x - flameWidth / 2, position.y + GameData::ROCKET_HEIGHT / 2);
            Vector2 flameRight(position.x + flameWidth / 2, position.y + GameData::ROCKET_HEIGHT / 2);

            ShapeRenderer::DrawTriangle(flameTop, flameLeft, flameRight, GameData::FLAME_COLOR);
        }
    }

};

// Инициализация статических членов Rocket
Vector2 Rocket::position;
Vector2 Rocket::velocity;
Vector2 Rocket::acceleration;
double Rocket::flameSize;
int Rocket::flameTarget;


void initialize() {
    Rocket::Initialize();
}


void act(float dt) {
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    Rocket::Update(static_cast<double>(dt));
}


void draw() {

    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    Rocket::Draw();
}


void finalize() {
}