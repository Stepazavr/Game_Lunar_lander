#pragma once


#include "Rocket.h"
#include "MoonSurface.h"
#include "Score.h"
#include "Vector2.h"
#include "Time.h"


#define NOGDI              // Отключает GDI-макросы
#define NOUSER             // Отключает USER-макросы
#include <windows.h>
#undef DrawText           // Отменяем макрос DrawText
#include <algorithm>



struct GameLogic {
    inline static bool isPause = false;

    static void pause() {
        Sleep(200);
        isPause = 1 - isPause;
    }

    static void initializeNewLevel() {
        Sleep(200);
        MoonSurface::Generate();
        Rocket::Initialize();
    }

    static void initializeNewSession() {
        Score::Reset();
        Time::Reset();
        initializeNewLevel();
    }


    static void gameLevelUpdate() {
        // Коллизия с поверхностью
        int surfaceIndex = -1;
        if (MoonSurface::CheckCollision(Rocket::GetPosition(), Rocket::GetDirection(), surfaceIndex)) {
            if (surfaceIndex > 0 && Rocket::GetAltitude() < 4.0 && std::abs(Rocket::GetAngleDegrees()) < 7.0 
                && Rocket::GetVelocity().Length() < 50) {
                //std::cout << "Rocket landed successfully!" << std::endl;
                Score::AddScore(surfaceIndex * 10);
                Sleep(1000);
                initializeNewLevel();
            }
            else {
                Rocket::Destroy();

            }
        }

    }

};





