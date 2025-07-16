#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <vector>


// Different part of Moon Surface (Surface Quality)
enum SurfaceQlty {
	Common,   // Common surface (no giving points)
	PointsX1, // Giving points with coeff 1
    PointsX2, // Giving points with coeff 1
    PointsX3, // Giving points with coeff 1
};


// The MoonSurface class is responsible for generating, collision and rendering the surface of the Moon (singleton)
class MoonSurface {
private:
	static std::vector<Vector2> surfacePoints; // Points on the Moon's surface
	static bool stopGenerate; // Flag for stopping surface generation
	static int demonX; // X-coordinate for range of view (for the Demon difficulty level)

public:
    static void Generate();
	static void Update();
    static void Draw();

    // Checking the object's collision with the surface
    static bool CheckCollision(const std::vector<Vector2>& objectShape, SurfaceQlty& surfaceQlty);

    // Getting the height of an object above the Moon's surface
    static double GetAltitudeAboveMoon(const Vector2& objectPos);

private:
    // Drawing a part of the Moon's surface from point A to point B
	static void DrawPart(const Vector2& A, const Vector2& B); 
    // Getting quality of part of surface
    static SurfaceQlty GetSurfaceQlty(const Vector2& A, const Vector2& B);
    // Checking if the point is under the surface
	static bool IsPointUnderSurface(const Vector2& point); 
    // Generation of a part of the mountain (up (c = 1) or down (c = -1))
    static void GeneratePartOfMauntain(double hLimit, int c);
    // Generating a straight mountain section
    static void GenerateStraightPartOfMauntain(); 
	// Getting the surface (2 points) under the object
    static std::pair<Vector2, Vector2> GetSurfaceUnderObject(const Vector2& objectPos);
	// Getting the direction of the next mountain (0 (down) or 1 (up))
	static int ChooseDirection(double hMin, double hMax);
};