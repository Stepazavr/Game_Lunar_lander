#include "GameData.h"
#include "Rocket.h"
#include "MoonSurface.h"
#include "HUD.h"
#include "GameLogic.h"
#include "Explosion.h"
#include "Complexity.h"
#include "Time.h"



#include <ctime>
#include <Windows.h>


void initializeLevel() {
    MoonSurface::Generate();
    Rocket::Initialize();
}


void initialize() {
    std::srand(static_cast<unsigned>(time(0)));

    //AllocConsole();
    //FILE* stream;
    //freopen_s(&stream, "CONOUT$", "w", stdout);
    //freopen_s(&stream, "CONOUT$", "w", stderr);

    initializeLevel();
}


void act(float dt) {
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();
    if (is_key_pressed(VK_SPACE))
        GameLogic::pause();
    if (is_key_pressed('C')) {
        Complexity::ChangeDifficulty();
        GameLogic::initializeNewSession();
    }
    if (GameLogic::isPause) return;

    Time::AddTime(double(dt));
    MoonSurface::Update();

    if (Rocket::IsAlive()) {
        Rocket::Update(double(dt));
        GameLogic::gameLevelUpdate();
    }
    else if (Explosion::IsActive()) {
        Explosion::Update(dt);
        if (!Explosion::IsActive())
            GameLogic::initializeNewSession();
    }
}


void draw() {

    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));


    if (Rocket::IsAlive()) {
        Rocket::Draw();
    }
    else if (Explosion::IsActive()) {
        Explosion::Draw();
    }

    MoonSurface::Draw();
	HUD::Draw();
}


void finalize() {
}