#pragma once


#include "Rocket.h"
#include "MoonSurface.h"
#include "Explosion.h"
#include "Score.h"
#include "Vector2.h"
#include "Time.h"
#include "GameData.h"

#include <windows.h>
#undef DrawText
#include <algorithm>


// (singleton)
struct GameLogic {
    inline static bool isPause = false;

	// On/off pause
    static void pause() {
        Sleep(GameData::SLEEP_PAUSE_TIME);
        isPause = 1 - isPause;
    }

    static void initializeNewLevel() {
        Sleep(GameData::SLEEP_LEVEL_TIME);
        MoonSurface::Generate();
        Rocket::Initialize();
    }

    static void initializeNewSession() {
        Score::Reset();
        Time::Reset();
        initializeNewLevel();
    }

	// Upgrade the level according to the logic of the game
    static void LevelUpdate() {
        if (!Rocket::IsAlive()) {
            if (!Explosion::IsActive())
                initializeNewSession();
            return;
		}

        // Collision with the surface causes the end of the level
        SurfaceQlty surfaceQlt = SurfaceQlty::Common;
        if (MoonSurface::CheckCollision(Rocket::GetShape(), surfaceQlt)) {
            if (surfaceQlt != SurfaceQlty::Common && Rocket::GetAltitude() < GameData::SUCCESSFUL_LANDED_HEIGHT
                && std::abs(Rocket::GetAngleDegrees()) < GameData::SUCCESSFUL_LANDED_ANGLE
                && Rocket::GetVelocity().Length() < GameData::SUCCESSFUL_LANDED_VELOCITY) {
                //Rocket landed successfully!
                Score::AddScore(int(surfaceQlt) * GameData::POINT_MODIFIER);
                initializeNewLevel();
            }
            else
                Rocket::Destroy();
        }
    }
};





