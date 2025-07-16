#pragma once

#include "GameData.h"
#include "Vector2.h"


// Rocket class (singleton)
class Rocket {
private:
    static Vector2 position;           // Rocket position
    static Vector2 direction;          // Rocket direction vector (from center to nose)
    static Vector2 velocity;           // Rocket velocity
    static Vector2 acceleration;       // Rocket acceleration
    static double angle;               // Current rotation angle (rad)
    static double altitudeAboveMoon;   // The altitude of the rocket above the surface of the moon
    static double thrust;              // Thrust force (0..1)
    static double fuel;                // Rocket fuel
    static bool isAlive;               // Does the rocket exist
    static std::vector<Vector2> shape; // The shape of the rocket (a sequence of points on a plane)
    
public:
    static Vector2 GetVelocity() { return velocity; }
	static Vector2 GetPosition() { return position; }
	static Vector2 GetDirection() { return direction; }
    static double GetAltitude() { return altitudeAboveMoon; }
    static double GetThrust() { return thrust; }
    static double GetAngleDegrees();
    static bool IsAlive() { return isAlive; }
	static double GetFuel() { return fuel; }
	static std::vector<Vector2> GetShape() { return shape; }

public:
    static void Initialize();

    static void Update(double dt);

    static void Draw();

	static void Destroy();

private:
    Rocket() = delete;

    static void UpdateRotation(double dt); // Updating the rotation angle of the rocket
    static void UpdateThrust(double dt);   // Updating rocket thrust
    static void ApplyPhysics(double dt);   // Applying physics to a rocket (acceleration, velocity and position)
    static void DrawRocketBody();          // Drawing the rocket body
    static void DrawRocketPorthole();        // Drawing the rocket porthole
    static void DrawRocketFlame();         // Rendering the rocket flame
    static void UpdateShape();             // Updating the shape of the rocket on plane
	static void ApplyScreenLimits();       // Applying screen limits to the rocket
	static void UpdateAltitude();          // Updating the altitudeAboveMoon of the rocket
};
