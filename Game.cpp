#include "GameData.h"
#include "Rocket.h"
#include "MoonSurface.h"
#include "HUD.h"
#include "GameLogic.h"
#include "Explosion.h"
#include "Complexity.h"


#include <ctime>
#include <Windows.h>


void initializeLevel() {
    Rocket::Initialize();
    MoonSurface::Generate();
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
        pause();
    if (is_key_pressed('C')) {
        Complexity::ChangeDifficulty();
        initializeNewLevel();
    }

    if (Rocket::IsAlive()) {
        Rocket::Update(static_cast<double>(dt));
        gameLevelUpdate();
    }
    else if (Explosion::IsActive()) {
        Explosion::Update(dt);
        if (!Explosion::IsActive()) 
			initializeNewLevel();
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