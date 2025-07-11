#include "MoonSurface.h"
#include "ShapeRenderer.h"


void MoonSurface::Generate() {
    surfacePoints.clear();
	stop_generate = false;

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

    const std::vector<double> moonLengths = { GameData::MOON_LENGTH_X1, GameData::MOON_LENGTH_X2,
                                        GameData::MOON_LENGTH_X3
    };


    double x = surfacePoints.back().x + moonLengths[rand() % moonLengths.size()];
    double y = surfacePoints.back().y;
    if (x >= SCREEN_WIDTH) {
        x = SCREEN_WIDTH;
        stop_generate = true;
    }
    surfacePoints.emplace_back(x, y);
}


// Рисование поверхности Луны
void MoonSurface::Draw() {
	uint32_t color = GameData::MOON_COLOR;
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        if (surfacePoints[i - 1].y == surfacePoints[i].y) {
            double length = surfacePoints[i].x - surfacePoints[i - 1].x;
            if (length <= GameData::MOON_LENGTH_X1 && length > GameData::MOON_LENGTH_X2)
                color = GameData::MOON_LANDING_COLOR;
			else if (length <= GameData::MOON_LENGTH_X2 && length > GameData::MOON_LENGTH_X3)
                color = GameData::DARK_ORANGE;
			else if (length <= GameData::MOON_LENGTH_X3)
				color = GameData::RED_3;
        } else
            color = GameData::MOON_COLOR;

        ShapeRenderer::DrawLine(surfacePoints[i - 1], surfacePoints[i], color);
    }
}

// Проверка коллизии ракеты с поверхностью
bool MoonSurface::CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir) {
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
bool MoonSurface::IsPointUnderSurface(const Vector2& point) {
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


// Инициализация статических членов MoonSurface
std::vector<Vector2> MoonSurface::surfacePoints;
bool MoonSurface::stop_generate = false;