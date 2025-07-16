#include "Explosion.h"
#include "GameData.h"
#include "ShapeRenderer.h"

#include <cstdlib>
#include <algorithm>


void Explosion::Start(const Vector2& pos) {
    position = pos;
    isActive = true;
    currentTime = 0.0;

    // Initialization of particles
    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
        // Random direction and speed
        double angle = double(rand()) / RAND_MAX * 2 * PI;
        double speed = GameData::EXPLOSION_MIN_SPEED + double(rand()) / RAND_MAX * 
            (GameData::EXPLOSION_MAX_SPEED - GameData::EXPLOSION_MIN_SPEED);

        velocities[i] = Vector2(cos(angle), sin(angle)) * speed;
        positions[i] = position;
    }
}

void Explosion::Update(double dt) {
    if (!isActive) return;

    currentTime += dt;
    // Updating the particle positions
    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
		velocities[i] = velocities[i] + GameData::GRAVITY_ACCELERATION * dt;
        positions[i] = positions[i] + velocities[i] * dt;
    }
    if (currentTime >= GameData::EXPLOSION_DURATION)
		Finish();
}

void Explosion::Draw() {
    if (!isActive) return;

    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
        uint32_t color = (currentTime < GameData::EXPLOSION_DURATION * GameData::COEFF_CHANGE_COLOR) ?
            GameData::EXPLOSION_COLOR : GameData::EXPLOSION_COLOR_2;

        int size = std::max(int(GameData::EXPLOSION_MAX_SIZE * (1 - currentTime) / GameData::EXPLOSION_DURATION),
                            GameData::EXPLOSION_MIN_SIZE);

        ShapeRenderer::DrawRect(int(positions[i].x), int(positions[i].y), size, size, color);
    }
}

void Explosion::Finish() {
    isActive = false;
}

bool Explosion::isActive = false;
double Explosion::currentTime = 0;
Vector2 Explosion::position;
std::vector<Vector2> Explosion::positions(GameData::EXPLOSION_PARTICLES_COUNT);
std::vector<Vector2> Explosion::velocities(GameData::EXPLOSION_PARTICLES_COUNT);