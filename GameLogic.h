#pragma once


#include "Rocket.h"
#include "MoonSurface.h"
#include "Score.h"
#include "Vector2.h"
#include "Time.h"

#define NOGDI              // ��������� GDI-�������
#define NOUSER             // ��������� USER-�������
#include <windows.h>
#undef DrawText           // �������� ������ DrawText
#include <algorithm>





struct GameLogic {
    inline static bool isPause = false;

    static void pause() {
        Sleep(200);
        isPause = 1 - isPause;
    }

    static void initializeNewLevel() {
        Sleep(200);
        Rocket::Initialize();
        MoonSurface::Generate();
    }

    static void initializeNewSession() {
        Score::Reset();
        Time::Reset();
        initializeNewLevel();
    }


    static void gameLevelUpdate() {
        // �������� � ������������
        int surfaceIndex = -1;
        if (MoonSurface::CheckCollision(Rocket::GetPosition(), Rocket::GetDirection(), surfaceIndex)) {
            if (surfaceIndex > 0 && Rocket::GetAltitude() < 5.0 && std::abs(Rocket::GetAngleDegrees()) < 10.0) {
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





