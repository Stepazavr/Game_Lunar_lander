#include "GameClass.h"


void initialize() {
    Rocket::Initialize();
    double r =  GameData::ROCKET_HEIGHT;
}


void act(float dt) {
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    Rocket::Update(static_cast<double>(dt));
}


void draw() {

    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    Rocket::Draw();
}


void finalize() {
}