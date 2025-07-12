#pragma once


#include "Rocket.h"
#include "MoonSurface.h"
#include "Score.h"
#include "Vector2.h"

#include <windows.h>
#include <algorithm>



void pause() {
    Sleep(100);
    while (!is_key_pressed(VK_SPACE)) {
        Sleep(1);
    }
    Sleep(100);
}

void gameLevelUpdate() {
    // Коллизия с поверхностью
    int surfaceIndex = -1;
    if (MoonSurface::CheckCollision(Rocket::GetPosition(), Rocket::GetDirection(), surfaceIndex)) {
        if (surfaceIndex > 0 && Rocket::GetAltitude() < 5.0 && std::abs(Rocket::GetAngleDegrees()) < 10.0) {
            //std::cout << "Rocket landed successfully!" << std::endl;
            Score::AddScore(surfaceIndex * 10);
        }
        else {
            Score::Reset();
        }
        Sleep(1000);
        Rocket::Initialize();
        MoonSurface::Generate();
        //Rocket::GetVelocity() = Vector2(0, 0);
    }

}