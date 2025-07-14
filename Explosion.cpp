#include "Explosion.h"
#include "GameData.h"
#include "ShapeRenderer.h"

#include <cstdlib>
#include <algorithm>


void Explosion::Start(const Vector2& pos) {
    position = pos;
    isActive = true;
    currentTime = 0;

    // Инициализация частиц
    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
        // Случайное направление и скорость
        double angle = double(rand()) / RAND_MAX * 2 * PI;
        double speed = GameData::EXPLOSION_MIN_SPEED + double(rand()) / RAND_MAX * 
            (GameData::EXPLOSION_MAX_SPEED - GameData::EXPLOSION_MIN_SPEED);

        velocities[i] = Vector2(cos(angle), sin(angle)) * speed;
        particles[i] = position;
    }
}

void Explosion::Update(double dt) {
    if (!isActive) return;

    currentTime += dt;

    // Обновление позиций частиц
    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
        particles[i] = particles[i] + velocities[i] * dt;
    }

    if (currentTime >= duration) {
		Finish();
    }
}

void Explosion::Draw() {
    if (!isActive) return;

    // Рисование частицы
    for (int i = 0; i < GameData::EXPLOSION_PARTICLES_COUNT; i++) {
        uint32_t color = (currentTime < duration * GameData::COEFF_CHANGE_COLOR) ? 
            GameData::EXPLOSION_COLOR : GameData::EXPLOSION__COLOR_2;

        int size = std::max(int(GameData::EXPLOSION_MAX_SIZE * (1 - currentTime) / duration), 
                            GameData::EXPLOSION_MIN_SIZE);

        ShapeRenderer::DrawRect(int(particles[i].x), int(particles[i].y), size, size, color);
    }
}

void Explosion::Finish() {
    isActive = false;
}


bool Explosion::isActive = false;
double Explosion::duration = GameData::EXPLOSION_DURATION;
double Explosion::currentTime = 0;
Vector2 Explosion::position;
std::vector<Vector2> Explosion::particles(GameData::EXPLOSION_PARTICLES_COUNT);
std::vector<Vector2> Explosion::velocities(GameData::EXPLOSION_PARTICLES_COUNT);