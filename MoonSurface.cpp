#include "MoonSurface.h"
#include "ShapeRenderer.h"
#include "Complexity.h"


double RandInInterval(double min, double max) {
    double res = min;
    if (min != max)
        res += rand() % int(max - min);
	return res;
}


void MoonSurface::Generate() {
    surfacePoints.clear();
	stop_generate = false;

    // Первая точка
    double x = 0;
    double y = SCREEN_HEIGHT - RandInInterval(GameData::MOON_MIN_HEIGHT_MAP, GameData::MOON_MAX_HEIGHT_MAP);
    surfacePoints.emplace_back(x, y);

    while (!stop_generate) {
        double h = SCREEN_HEIGHT - surfacePoints.back().y;
        double h_max = RandInInterval(h, GameData::MOON_MAX_HEIGHT_MAP);
        double h_min = RandInInterval(GameData::MOON_MIN_HEIGHT_MAP, h_max);

        GeneratePartOfMauntain(h_max, 1);
        GenerateStraightPartOfMauntain();
        GeneratePartOfMauntain(h_min, -1);
        GenerateStraightPartOfMauntain();
    }
}

// Генерация длины участка поверхности
double MoonSurface::Rand_length() {
    return RandInInterval(GameData::MOON_MIN_LENGTH, GameData::MOON_MAX_LENGTH);
}

// Генерация высоты участка поверхности
double MoonSurface::Rand_height() {
    return RandInInterval(GameData::MOON_MIN_HEIGHT, GameData::MOON_MAX_HEIGHT);
}

// Генерация части горы (возвышение (c = 1) или спад (c = -1))
void MoonSurface::GeneratePartOfMauntain(double h_limit, int c) {
    if (stop_generate) return;
    bool go = true;
    while (go) {
        double x = surfacePoints.back().x + Rand_length();
        double h = SCREEN_HEIGHT - surfacePoints.back().y + c * Rand_height();
        if (c * h >= c * h_limit) {
            h = h_limit;
            go = false;
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

// Генерация прямого участка горы
void MoonSurface::GenerateStraightPartOfMauntain() {
    if (stop_generate) return;

    const std::vector<double> moonLengths = { GameData::MOON_LENGTH_X1, GameData::MOON_LENGTH_X2,
                                        GameData::MOON_LENGTH_X3
    };

	int leftIndex = std::max(int(Complexity::GetDifficulty()) - 1, 0);
	int rightIndex = std::min(int(Complexity::GetDifficulty()) + 1, int(moonLengths.size()) - 1);


    double x = surfacePoints.back().x + moonLengths[leftIndex + rand() % (rightIndex - leftIndex + 1)];
    double y = surfacePoints.back().y;
    if (x >= SCREEN_WIDTH) {
        x = SCREEN_WIDTH;
        stop_generate = true;
    }
    surfacePoints.emplace_back(x, y);
}


// Рисование поверхности Луны
void MoonSurface::Draw() {
    std::vector<std::string> stringPoints = { "", "+10", "+20", "+30" };
    std::vector<uint32_t> colorPoints = { GameData::MOON_COLOR, GameData::GREEN,
		GameData::DARK_ORANGE, GameData::RED_3 };

    double pointsScale = 2;
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        double surfaceIndex = GetSurfaceIndex(surfacePoints[i - 1], surfacePoints[i]);

        double pointsX = (surfacePoints[i - 1].x + surfacePoints[i].x) / 2 -
            PIXELFONT_W * (stringPoints[surfaceIndex].length() + 1);
        double pointsY = surfacePoints[i].y + GameData::POINTS_INFO_MARGIN_Y;

        ShapeRenderer::DrawText(pointsX, pointsY, 
            stringPoints[surfaceIndex], colorPoints[surfaceIndex], pointsScale);

        ShapeRenderer::DrawLine(surfacePoints[i - 1], surfacePoints[i], colorPoints[surfaceIndex]);
    }
}

// Проверка коллизии ракеты с поверхностью
bool MoonSurface::CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir, int& surfaceIndex) {
    // 1. Получаем три вершины ракеты (нос, левый и правый угол)
    Vector2 nose = rocketPos + rocketDir * (GameData::ROCKET_HEIGHT / 2);
    Vector2 left = rocketPos - rocketDir * (GameData::ROCKET_HEIGHT / 2) +
        Vector2(-rocketDir.y, rocketDir.x) * (GameData::ROCKET_WIDTH / 2);
    Vector2 right = rocketPos - rocketDir * (GameData::ROCKET_HEIGHT / 2) +
        Vector2(-rocketDir.y, rocketDir.x) * (-GameData::ROCKET_WIDTH / 2);


    std::pair<Vector2, Vector2> leftSurface = GetSurfaceUnderRocket(left);
	std::pair<Vector2, Vector2> rightSurface = GetSurfaceUnderRocket(right);

    int leftSurfaceIndex = GetSurfaceIndex(leftSurface.first, leftSurface.second);
	int rightSurfaceIndex = GetSurfaceIndex(rightSurface.first, rightSurface.second);

	surfaceIndex = (leftSurfaceIndex == rightSurfaceIndex) ? leftSurfaceIndex : 0;

    // 2. Проверяем каждую точку ракеты на пересечение с поверхностью
    return IsPointUnderSurface(nose) ||
        IsPointUnderSurface(left) ||
        IsPointUnderSurface(right);
}

int MoonSurface::GetSurfaceIndex(const Vector2& A, const Vector2& B) {
    if (A.y != B.y) return 0;
    double length = std::abs(B.x - A.x);
    if (length > GameData::MOON_LENGTH_X1)
        return -1;
    else if (length > GameData::MOON_LENGTH_X2)
        return 1;
    else if (length > GameData::MOON_LENGTH_X3)
        return 2;
    else
        return 3;
}

// Вспомогательная функция: проверяет, находится ли точка под поверхностью
bool MoonSurface::IsPointUnderSurface(const Vector2& point) {
    return GetAltitudeAboveMoon(point) <= 0;
}

// Получение высоты ракеты над поверхностью Луны
double MoonSurface::GetAltitudeAboveMoon(const Vector2& rocketPos) {
    std::pair<Vector2, Vector2> surface = GetSurfaceUnderRocket(rocketPos);
    double t = (rocketPos.x - surface.first.x) / (surface.second.x - surface.first.x);
    double surfaceY = surface.first.y + t * (surface.second.y - surface.first.y);
    return surfaceY - rocketPos.y; // Высота над поверхностью
}

std::pair<Vector2, Vector2> MoonSurface::GetSurfaceUnderRocket(const Vector2& rocketPos) {
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        if (rocketPos.x >= surfacePoints[i - 1].x && rocketPos.x <= surfacePoints[i].x)
			return { surfacePoints[i - 1], surfacePoints[i] };
    }

}

// Инициализация статических членов MoonSurface
std::vector<Vector2> MoonSurface::surfacePoints;
bool MoonSurface::stop_generate = false;