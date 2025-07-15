#include "MoonSurface.h"
#include "ShapeRenderer.h"
#include "Complexity.h"
#define NOMINMAX


double RandInInterval(double min, double max) {
    if (min > max) {
        std::swap(min, max);
	}
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
        double h_max = RandInInterval(h + GameData::MOON_MIN_HEIGHT_MOUNTAIN, GameData::MOON_MAX_HEIGHT_MAP);
        double h_min = RandInInterval(GameData::MOON_MIN_HEIGHT_MAP, h - GameData::MOON_MIN_HEIGHT_MOUNTAIN);
		std::vector<double> hLimits = { h_min, h_max };

        int direction = ChooseDirection(h_min, h_max); // 0 (спад) или 1 (возвышение)

        GeneratePartOfMauntain(hLimits[direction], 2 * direction - 1);

        if (surfacePoints.back().x < GameData::MAX_ALLOWED_STRAIGHT_X)
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


	int leftIndex = std::max(int(Complexity::GetDifficulty()) - 1, 0);
	int rightIndex = std::min(int(Complexity::GetDifficulty()) + 1, int(GameData::MOON_LENGTHS.size()) - 1);

    int index = rand() % GameData::MAP_LINES.at(Complexity::GetDifficulty()).size();

    double x = surfacePoints.back().x + GameData::MOON_LENGTHS[GameData::MAP_LINES.at(Complexity::GetDifficulty())[index] - 1];
    double y = surfacePoints.back().y;
    if (x >= SCREEN_WIDTH) {
        x = SCREEN_WIDTH;
        stop_generate = true;
    }
    surfacePoints.emplace_back(x, y);
}


void MoonSurface::Update() {
    if (Complexity::GetDifficulty() == Difficulty::Demon)
        demonX = (demonX + 1) % SCREEN_WIDTH;
}

// Рисование поверхности Луны
void MoonSurface::Draw() {
    for (size_t i = 1; i < surfacePoints.size(); ++i) {
        if (Complexity::GetDifficulty() == Difficulty::Demon) {
            if ((surfacePoints[i].x < demonX ||
                surfacePoints[i].x > demonX + GameData::DEMONS_RANGE_OF_VIEW))
                continue;
        }
        DrawPart(surfacePoints[i - 1], surfacePoints[i]);
    }
}

void MoonSurface::DrawPart(const Vector2& A, const Vector2& B) {
    double surfaceIndex = GetSurfaceIndex(A, B);

    double pointsX = (A.x + B.x) / 2 -
        PIXELFONT_W * (GameData::STRING_POINTS[surfaceIndex].length() + 1);
    double pointsY = B.y + GameData::POINTS_INFO_MARGIN_Y;

    ShapeRenderer::DrawText(pointsX, pointsY,
        GameData::STRING_POINTS[surfaceIndex], GameData::COLOR_POINTS[surfaceIndex], GameData::POINTS_SCALE);

    ShapeRenderer::DrawLine(A, B, GameData::COLOR_POINTS[surfaceIndex]);
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

// 0 (спад) или 1 (возвышение)
int MoonSurface::ChooseDirection(double h_min, double h_max) {
    if (h_min <= double(GameData::MOON_MIN_HEIGHT_MAP))
        return 1;
    else if (h_max >= double(GameData::MOON_MAX_HEIGHT_MAP))
        return 0;
    else
        return rand() % 2;
}
// Инициализация статических членов MoonSurface
std::vector<Vector2> MoonSurface::surfacePoints;
bool MoonSurface::stop_generate = false;
int MoonSurface::demonX = 0;