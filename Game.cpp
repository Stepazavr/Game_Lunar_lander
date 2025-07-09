#include "GameClass.h"

#include <ctime>
#include <Windows.h>


void initialize() {
    std::srand(static_cast<unsigned>(time(0)));

    //AllocConsole();
    //FILE* stream;
    //freopen_s(&stream, "CONOUT$", "w", stdout);
    //freopen_s(&stream, "CONOUT$", "w", stderr);

    Rocket::Initialize();
    MoonSurface::Generate();
}


void act(float dt) {
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    Rocket::Update(static_cast<double>(dt));
}


void draw() {

    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    Rocket::Draw();
    MoonSurface::Draw();
}


void finalize() {
}