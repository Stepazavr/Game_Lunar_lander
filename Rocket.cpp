#include "Rocket.h"
#include "MoonSurface.h"
#include "ShapeRenderer.h"
#include "Explosion.h"
#include "Complexity.h"

#include <cmath>
#include <algorithm>


double Rocket::GetAngleDegrees() {
    double normAngle = std::fmod(angle, 2.0 * PI);
    if (normAngle > PI) normAngle -= 2.0 * PI;
    if (normAngle < -PI) normAngle += 2.0 * PI;
	return normAngle * 180.0 / PI;
}

void Rocket::Initialize() {
    position = Vector2(GameData::START_ROCKET_X, GameData::START_ROCKET_Y);
    direction = Vector2(0.0, -1.0);
    velocity = Vector2(0.0, 0.0);
    acceleration = GameData::GRAVITY_ACCELERATION;
    angle = 0.0;
    altitudeAboveMoon = MoonSurface::GetAltitudeAboveMoon(position - direction * (GameData::ROCKET_HEIGHT / 2));
    thrust = 0.0;
	fuel = GameData::DIFFICULTY_CONFIG.at(Complexity::GetDifficulty()).fuel;
	isAlive = true;
    Rocket::shape = ShapeRenderer::CreateTriangle(position, direction, GameData::ROCKET_HEIGHT, GameData::ROCKET_WIDTH);
}

void Rocket::Update(double dt) {
	if (!isAlive) return;

    UpdateRotation(dt);
    UpdateThrust(dt);
    ApplyPhysics(dt);

    UpdateShape();
    ApplyScreenLimits();
    UpdateAltitude();
}

void Rocket::Draw() {
    DrawRocketBody();
    DrawRocketPorthole();
    if (thrust > GameData::THRUST_MIN_VAL) {
        DrawRocketFlame();
    }
}

// Updating the rotation angle of the rocket
void Rocket::UpdateRotation(double dt) {
    double rotation = 0.0;

    if (is_key_pressed(VK_LEFT)) {
        rotation = GameData::ROTATION_SPEED * dt;
    }
    if (is_key_pressed(VK_RIGHT)) {
        rotation = -GameData::ROTATION_SPEED * dt;
    }
    angle += rotation;
    // Updating the direction vector
    direction.x = -sin(angle);
    direction.y = -cos(angle);
}

// Updating rocket thrust
void Rocket::UpdateThrust(double dt) {
	bool thrustTarget = (is_mouse_button_pressed(0) && (fuel > 0)) ? 1 : 0; // is the engine running
    thrust += (thrustTarget - thrust) * GameData::THRUST_SPEED * dt;
    thrust = std::max(0.0, std::min(1.0, thrust));

	fuel -= thrustTarget * GameData::FUEL_CONSUMPTION_RATE * dt;
	fuel = std::max(0.0, fuel);
}

// Applying physics to a rocket (acceleration, velocity and position)
void Rocket::ApplyPhysics(double dt) {
    acceleration = GameData::GRAVITY_ACCELERATION;

    // Adding acceleration from thrust
    if (thrust > GameData::THRUST_MIN_VAL) {
        Vector2 thrustForce = direction * GameData::MAX_THRUST_FORCE * thrust;
        acceleration = acceleration + thrustForce;
    }
    // Updating velocity and position
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
}

// Updating the shape of the rocket on plane
void Rocket::UpdateShape() {
    Rocket::shape = ShapeRenderer::CreateTriangle(position, direction, GameData::ROCKET_HEIGHT, GameData::ROCKET_WIDTH);
}

// Applying screen limits to the rocket
void Rocket::ApplyScreenLimits() {
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

// Updating the altitudeAboveMoon of the rocket
void Rocket::UpdateAltitude() {
    altitudeAboveMoon = MoonSurface::GetAltitudeAboveMoon(position - direction * (GameData::ROCKET_HEIGHT / 2));
}

// Drawing the rocket body
void Rocket::DrawRocketBody() {
    ShapeRenderer::DrawTriangle(shape[0], shape[1], shape[2], 
        GameData::DIFFICULTY_CONFIG.at(Complexity::GetDifficulty()).rocketColor);
}

// Drawing the rocket porthole
void Rocket::DrawRocketPorthole() {
    Vector2 portholePos = position + direction * GameData::PORTHOLE_OFFSET_Y;
    ShapeRenderer::DrawCircle(portholePos, GameData::PORTHOLE_RADIUS, GameData::PORTHOLE_COLOR);
}

// Rendering the rocket flame
void Rocket::DrawRocketFlame() {
    double flameHeight = GameData::FLAME_MAX_HEIGHT * thrust;
    double flameWidth = GameData::FLAME_MAX_WIDTH * thrust;

    Vector2 flamePos = position - direction * (GameData::ROCKET_HEIGHT / 2 + flameHeight / 2);
    std::vector<Vector2> flameTr = ShapeRenderer::CreateTriangle(flamePos, direction * (-1), flameHeight, flameWidth);

    ShapeRenderer::DrawTriangle(flameTr[0], flameTr[1], flameTr[2], GameData::FLAME_COLOR);
}

void Rocket::Destroy() {
    isAlive = false;
    Explosion::Start(position);
}

// Initialization of static Rocket members
Vector2 Rocket::position;
Vector2 Rocket::direction;
Vector2 Rocket::velocity;
Vector2 Rocket::acceleration;
double Rocket::angle;
double Rocket::altitudeAboveMoon;
double Rocket::thrust;
double Rocket::fuel;
bool Rocket::isAlive;
std::vector<Vector2> Rocket::shape;