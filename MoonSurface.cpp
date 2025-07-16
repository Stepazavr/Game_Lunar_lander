#include "MoonSurface.h"
#include "ShapeRenderer.h"
#include "Complexity.h"

// getting a random number on the segment [min, max]
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
	stopGenerate = false;

    // First point
    double x = GameData::MOON_SURFACE_START_POINT_X;
    double y = SCREEN_HEIGHT - RandInInterval(GameData::MOON_MIN_HEIGHT_MAP, GameData::MOON_MAX_HEIGHT_MAP);
    surfacePoints.emplace_back(x, y);

    while (!stopGenerate) {
        double h = SCREEN_HEIGHT - surfacePoints.back().y;
        double hMax = RandInInterval(h + GameData::MOON_MIN_HEIGHT_MOUNTAIN, GameData::MOON_MAX_HEIGHT_MAP);
        double hMin = RandInInterval(GameData::MOON_MIN_HEIGHT_MAP, h - GameData::MOON_MIN_HEIGHT_MOUNTAIN);
		std::vector<double> hLimits = { hMin, hMax };

        int direction = ChooseDirection(hMin, hMax); // 0 (down) или 1 (up)

        GeneratePartOfMauntain(hLimits[direction], 2 * direction - 1);

        if (surfacePoints.back().x < GameData::MAX_ALLOWED_STRAIGHT_X)
            GenerateStraightPartOfMauntain();
    }
}

// Generation of a part of the mountain (up (c = 1) or down (c = -1))
void MoonSurface::GeneratePartOfMauntain(double hLimit, int c) {
    if (stopGenerate) return;
    bool go = true;
    while (go) {
        double x = surfacePoints.back().x + RandInInterval(GameData::MOON_MIN_LENGTH, GameData::MOON_MAX_LENGTH);
        double h = SCREEN_HEIGHT - surfacePoints.back().y + 
                   c * RandInInterval(GameData::MOON_MIN_HEIGHT, GameData::MOON_MAX_HEIGHT);
        if (c * h >= c * hLimit) {
            h = hLimit;
            go = false;
        }
        double y = SCREEN_HEIGHT - h;
        if (x >= GameData::MOON_SURFACE_FINISH_POINT_X) {
            x = GameData::MOON_SURFACE_FINISH_POINT_X;
            stopGenerate = true;
        }
        surfacePoints.emplace_back(x, y);
        if (stopGenerate) return;
    }
}

// Generating a straight mountain section
void MoonSurface::GenerateStraightPartOfMauntain() {
    if (stopGenerate) return;
    const auto& pointsCoeff = GameData::DIFFICULTY_CONFIG.at(Complexity::GetDifficulty()).pointsCoeff;
    int index = rand() % pointsCoeff.size();

    double x = surfacePoints.back().x + GameData::MOON_LENGTHS[pointsCoeff[index] - 1];
    double y = surfacePoints.back().y;
    if (x >= GameData::MOON_SURFACE_FINISH_POINT_X) {
        x = GameData::MOON_SURFACE_FINISH_POINT_X;
        stopGenerate = true;
    }
    surfacePoints.emplace_back(x, y);
}

void MoonSurface::Update() {
    if (Complexity::GetDifficulty() == Difficulty::Demon)
        demonX = (demonX + 1) % GameData::MOON_SURFACE_FINISH_POINT_X;
}

void MoonSurface::Draw() {
    for (int i = 1; i < surfacePoints.size(); i++) {
        if (Complexity::GetDifficulty() == Difficulty::Demon) {
            if ((surfacePoints[i].x < demonX ||
                surfacePoints[i].x > demonX + GameData::DEMONS_RANGE_OF_VIEW))
                continue;
        }
        DrawPart(surfacePoints[i - 1], surfacePoints[i]);
    }
}

// Drawing a part of the Moon's surface from point A to point B
void MoonSurface::DrawPart(const Vector2& A, const Vector2& B) {
    double surfaceQlty = GetSurfaceQlty(A, B);

    double pointsX = (A.x + B.x) / 2 -
        PIXELFONT_W * (GameData::STRING_POINTS[surfaceQlty].length() + 1);
    double pointsY = B.y + GameData::POINTS_INFO_MARGIN_Y;

    ShapeRenderer::DrawText(pointsX, pointsY,
        GameData::STRING_POINTS[surfaceQlty], GameData::COLOR_POINTS[surfaceQlty], GameData::POINTS_SCALE);

    ShapeRenderer::DrawLine(A, B, GameData::COLOR_POINTS[surfaceQlty]);
}

// Checking the object's collision with the surface
bool MoonSurface::CheckCollision(const std::vector<Vector2>& objectShape, SurfaceQlty& surfaceQlty) {
    // Finding the lowest points
    Vector2 left = objectShape[0];
    Vector2 right = objectShape[0];

    for (const auto& point : objectShape) {
        if (point.y > left.y) {
            left = right = point;
        }
        else if (point.y == left.y) {
            if (point.x < left.x) left = point;
            if (point.x > right.x) right = point;
        }
    }

    std::pair<Vector2, Vector2> leftSurfacePair = GetSurfaceUnderObject(left);
    std::pair<Vector2, Vector2> rightSurfacePair = GetSurfaceUnderObject(right);

    SurfaceQlty leftSurfaceQlty = GetSurfaceQlty(leftSurfacePair.first, leftSurfacePair.second);
    SurfaceQlty rightSurfaceQlty = GetSurfaceQlty(rightSurfacePair.first, rightSurfacePair.second);

    surfaceQlty = (leftSurfaceQlty == rightSurfaceQlty) ? leftSurfaceQlty : SurfaceQlty::Common;

    for (const auto& point : objectShape) {
        if (IsPointUnderSurface(point))
            return true;
    }
    return false;
}

// Getting quality of part of surface
SurfaceQlty MoonSurface::GetSurfaceQlty(const Vector2& A, const Vector2& B) {
    if (A.y != B.y) return SurfaceQlty::Common;
    double length = std::abs(B.x - A.x);
    if (length > GameData::MOON_LENGTHS[0])
        return SurfaceQlty::Common;
    else if (length > GameData::MOON_LENGTHS[1])
        return SurfaceQlty::PointsX1;
    else if (length > GameData::MOON_LENGTHS[2])
        return SurfaceQlty::PointsX2;
    else
        return SurfaceQlty::PointsX3;
}

// Checking if the point is under the surface
bool MoonSurface::IsPointUnderSurface(const Vector2& point) {
    return GetAltitudeAboveMoon(point) <= 0.0;
}

// Getting the height of an object above the Moon's surface
double MoonSurface::GetAltitudeAboveMoon(const Vector2& objectPos) {
    std::pair<Vector2, Vector2> surfacePair = GetSurfaceUnderObject(objectPos);
    double t = (objectPos.x - surfacePair.first.x) / (surfacePair.second.x - surfacePair.first.x);
    double surfaceY = surfacePair.first.y + t * (surfacePair.second.y - surfacePair.first.y);
    return surfaceY - objectPos.y; // Height above the surface
}

// Getting the surface (2 points) under the object
std::pair<Vector2, Vector2> MoonSurface::GetSurfaceUnderObject(const Vector2& objectPos) {
    for (int i = 1; i < surfacePoints.size(); i++) {
        if (objectPos.x >= surfacePoints[i - 1].x && objectPos.x <= surfacePoints[i].x)
			return { surfacePoints[i - 1], surfacePoints[i] };
    }
}

// Getting the direction of the next mountain (0 (down) or 1 (up))
int MoonSurface::ChooseDirection(double hMin, double hMax) {
    if (hMin <= double(GameData::MOON_MIN_HEIGHT_MAP))
        return 1;
    else if (hMax >= double(GameData::MOON_MAX_HEIGHT_MAP))
        return 0;
    else
        return rand() % 2;
}

// Initializing static MoonSurface members
std::vector<Vector2> MoonSurface::surfacePoints;
bool MoonSurface::stopGenerate = false;
int MoonSurface::demonX = 0;