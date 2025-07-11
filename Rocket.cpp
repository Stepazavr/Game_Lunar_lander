#include "Rocket.h"
#include "MoonSurface.h"
#include "ShapeRenderer.h"


#include <math.h>
#include <algorithm>


// ������������� ������
void Rocket::Initialize() {
    position = Vector2(GameData::START_ROCKET_X, GameData::START_ROCKET_Y);
    direction = Vector2(0, -1);
    velocity = Vector2(0, 0);
    acceleration = Vector2(0, GameData::GRAVITY);
    angle = 0;
    altitudeAboveMoon = SCREEN_HEIGHT;

    flameSize = 0.0;
    thrust = 0;
}

// ���������� ��������� ������
void Rocket::Update(double dt) {

    UpdateRotation(dt);
    UpdateThrust(dt);
    ApplyPhysics(dt);

    // ����������� � �������� ������
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
    altitudeAboveMoon = MoonSurface::GetAltitudeAboveMoon(position - direction * (GameData::ROCKET_HEIGHT / 2));

    // �������� � ������������
    if (MoonSurface::CheckCollision(position, direction)) {
        if (altitudeAboveMoon < 1.0 && std::abs(angle) < 1.0) {
            //std::cout << "Rocket landed successfully!" << std::endl;
        }
        else {
            //std::cout << "Rocket crashed!" << std::endl;
            //schedule_quit_game();
        }
        velocity = Vector2(0, 0);
    }
}

// ��������� ������
void Rocket::Draw() {
    DrawRocketBody();
    DrawRocketWindow();
    if (thrust > GameData::THRUST_MIN_VAL) {
        DrawRocketFlame();
    }
}

// ���������� ���� �������� ������
void Rocket::UpdateRotation(double dt) {
    double rotation = 0.0;

    if (is_key_pressed(VK_LEFT)) {
        rotation = -GameData::ROTATION_SPEED * dt;
    }
    if (is_key_pressed(VK_RIGHT)) {
        rotation = GameData::ROTATION_SPEED * dt;
    }
    angle += rotation;
    // ��������� ������ �����������
    direction.x = sin(angle);
    direction.y = -cos(angle);
}

// ���������� ���� ������
void Rocket::UpdateThrust(double dt) {
    int thrustTarget = is_mouse_button_pressed(0) ? 1 : 0;
    thrust += (thrustTarget * GameData::MAX_THRUST - thrust) * GameData::THRUST_SPEED * dt;
    thrust = std::max(0.0, std::min(GameData::MAX_THRUST, thrust));

    // ������ ������� �������������� ����
    flameSize = thrust;
}

// ���������� ������ � ������
void Rocket::ApplyPhysics(double dt) {
    // ����������� ��������� �� ����������
    acceleration = Vector2(0, GameData::GRAVITY);

    // ���������� ��������� �� ����
    if (thrust > GameData::THRUST_MIN_VAL) {
        Vector2 thrustForce = direction * GameData::MAX_THRUST_FORCE * thrust;
        acceleration = acceleration + thrustForce;
    }
    // ���������� �������� � �������
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
}

// ��������� ���� ������
void Rocket::DrawRocketBody() {
    Vector2 top = position + direction * (GameData::ROCKET_HEIGHT / 2);

    Vector2 perpendicular(-direction.y, direction.x);
    Vector2 left = position - direction * (GameData::ROCKET_HEIGHT / 2)
        - perpendicular * (GameData::ROCKET_WIDTH / 2);
    Vector2 right = position - direction * (GameData::ROCKET_HEIGHT / 2)
        + perpendicular * (GameData::ROCKET_WIDTH / 2);

    ShapeRenderer::DrawTriangle(top, left, right, GameData::ROCKET_COLOR);
}

// ��������� ���� ������
void Rocket::DrawRocketWindow() {
    Vector2 windowPos = position + direction * GameData::WINDOW_OFFSET_Y;
    ShapeRenderer::DrawCircle(windowPos, GameData::WINDOW_RADIUS, GameData::WINDOW_COLOR);
}

// ��������� ������� ������
void Rocket::DrawRocketFlame() {
    double flameHeight = GameData::FLAME_MAX_HEIGHT * flameSize;
    double flameWidth = GameData::FLAME_MAX_WIDTH * flameSize;

    // ��������� ������� (����� ������ ������)
    Vector2 flameBase = position - direction * (GameData::ROCKET_HEIGHT / 2);

    // ������� �������
    Vector2 flameTip = flameBase - direction * flameHeight;

    Vector2 perpendicular(-direction.y, direction.x);
    Vector2 flameLeft = flameBase - perpendicular * (flameWidth / 2);
    Vector2 flameRight = flameBase + perpendicular * (flameWidth / 2);

    ShapeRenderer::DrawTriangle(flameTip, flameLeft, flameRight, GameData::FLAME_COLOR);
}


// ������������� ����������� ������ Rocket
Vector2 Rocket::position;
Vector2 Rocket::direction;
Vector2 Rocket::velocity;
Vector2 Rocket::acceleration;
double Rocket::angle;
double Rocket::altitudeAboveMoon;
double Rocket::flameSize;
double Rocket::thrust;