#pragma once

#include "Engine.h"
#include "Complexity.h"
#include "Vector2.h"

#include <vector>
#include <map>


#define PI 3.14159265358979323846
#define PIXELFONT_H 7
#define PIXELFONT_W 5


namespace Color {
    constexpr uint32_t WHITE = 0xFFFFFFFF;
    constexpr uint32_t GRAY = 0xFF808080;
    constexpr uint32_t ORANGE = 0xFFFFA500;
    constexpr uint32_t DARK_ORANGE = 0xFFFFA500;
    constexpr uint32_t GREEN = 0xFF00FF00;
    constexpr uint32_t RED = 0xFFB22222;
    constexpr uint32_t RED_2 = 0xFFc22542;
	constexpr uint32_t BLUE = 0xFF0008ff;
	constexpr uint32_t Violet = 0xFF4b36d6;
	constexpr uint32_t PINK = 0xFF8c1bb5;
};

// Namespace for all constants
namespace GameData {

    // Constants of the game window
    constexpr double WINDOW_MARGIN_X = 20.0; // X-offset (this is where the game area begins)
    constexpr double WINDOW_MARGIN_Y = 40.0; // Y-offset

    // Rocket launch position
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = WINDOW_MARGIN_Y + 0.0;

    // Geometric parameters of the rocket
    constexpr double ROCKET_HEIGHT = 40.0;
    constexpr double ROCKET_WIDTH = 30.0;
    constexpr double PORTHOLE_RADIUS = 5.0;
    constexpr double PORTHOLE_OFFSET_Y = 0.0;

    // Geometric parameters of flame
    constexpr double FLAME_MAX_HEIGHT = 20.0;
    constexpr double FLAME_MAX_WIDTH = 15.0;

    // Physical parameters of the rocket
	constexpr double ROTATION_SPEED = 3.0;       // Rotation speed [rad/s]
    constexpr double MAX_THRUST_FORCE = 200.0;   // Maximum thrust force [pixels/s^2]
	constexpr double THRUST_MIN_VAL = 0.01;      // Threshold value for the existence of thrust
	constexpr double THRUST_SPEED = 5.0;         // Thrust speed (acceleration jerk) [pixels/s^3]
    constexpr double FUEL_CONSUMPTION_RATE = 10; //  Fuel consumption [L/s]

    // Rocket color parameters
    constexpr uint32_t PORTHOLE_COLOR = Color::WHITE; // Белый
    constexpr uint32_t FLAME_COLOR = Color::ORANGE;  // Оранжевый

	// Common Logical constants
	constexpr double GRAVITY = 50.0; // [pixels/^2]

    // Geometric parameters of the Moon surface
	constexpr double MOON_MIN_HEIGHT_MAP = 100.0;  // Minimum height of the surface on the screen
	constexpr double MOON_MAX_HEIGHT_MAP = 400.0;  // Maximum height of the surface on the screen
	constexpr double MOON_MIN_HEIGHT_MOUNTAIN = 50.0; // Minimum height of the mountain
	constexpr double MOON_MIN_LENGTH = 5.0; // Minimum length of the part of surface
    constexpr double MOON_MAX_LENGTH = 10.0; // Maximum length of the part of surface
	constexpr double MOON_MIN_HEIGHT = 5.0; // Minimum height of the part of surface
    constexpr double MOON_MAX_HEIGHT = 10.0; // Maximum height of the part of surface
    constexpr double MOON_SURFACE_START_POINT_X = 0.0; // The initial X coordinate for the Moon's surface
    constexpr double MOON_SURFACE_FINISH_POINT_X = SCREEN_WIDTH; // The final X coordinate for the Moon's surface
    // The length of the part of surface with the coefficient of points { x1, x2, x3 }
    const std::vector<double> MOON_LENGTHS = { 120.0, 60.0, 40.0 };
	const double MAX_ALLOWED_STRAIGHT_X = MOON_SURFACE_FINISH_POINT_X - MOON_LENGTHS[0]; // The maximum X coordinate for the straight part of the surface
    

    // Moon color parameters
    constexpr uint32_t MOON_COLOR = Color::WHITE;
	

    // Points' parametrs
    constexpr double POINTS_INFO_MARGIN_Y = 15.0; // Y-indentation for information about points
    constexpr double POINTS_SCALE = 2.0; // Scale of the points symbols
    const std::vector<uint32_t> COLOR_POINTS = { MOON_COLOR,
                                                 Color::GREEN,
                                                 Color::DARK_ORANGE,
                                                 Color::RED
                                                }; // Colors for points

    constexpr double DEMONS_RANGE_OF_VIEW = 80.0; // Viewing range for difficulty:demon
	constexpr double DEMON_SCROLL_SPEED = 420.0; // Speed of scrolling the demon's surface [pixels/s]


    // Geometric interface parameters
    constexpr double HUD_MARGIN_Y = 30.0; // Y-coordinate distance between lines of text
    constexpr double HUD_MARGIN_X = 1.0; // X-coordinate distance between symbols of text
    constexpr double HUD_SCALE_COMMON = 2.0; // Scaling the interface

    // Indentation for the left block
    constexpr double HUD_PADDING_LEFT_X = 30.0;
	constexpr double HUD_PADDING_LEFT_Y = 30.0;

    // Indentation for the right block
	constexpr double HUD_PADDING_RIGHT_X = SCREEN_WIDTH - 250.0;
	constexpr double HUD_PADDING_RIGHT_Y = 30.0;

    // Bar parameters
    constexpr double HUD_BAR_WIDTH = 100.0;
    constexpr double HUD_BAR_HEIGHT = 10.0;

	// Other interface parameters
	constexpr double HUD_VAL_SCALE = 0.1; // the scaling factor of the values in the interface

	// Pause icon parameters
	constexpr double HUD_PAUSE_ICON_POSITION= 750.0; // Position for the pause icon
	constexpr int HUD_PAUSE_ICON_SIZE = 10; // The size of the pause icon

    // Interface color parameters
    constexpr uint32_t HUD_TEXT_COLOR = Color::WHITE;
    constexpr uint32_t HUD_BAR_EMPTY_COLOR = Color::GRAY;
    constexpr uint32_t HUD_BAR_COLOR = Color::GREEN;
	constexpr uint32_t HUD_PAUSE_ICON_COLOR = Color::GRAY;


    // Explosion parameters
    constexpr int EXPLOSION_PARTICLES_COUNT = 50; // Number of explosion particles
    constexpr double EXPLOSION_DURATION = 1.0; // Duration of the explosion in seconds
    constexpr double EXPLOSION_MIN_SPEED = 50.0; // Minimum particle velocity of the explosion
	constexpr double EXPLOSION_MAX_SPEED = 150.0; // Maximum particle velocity of the explosion
    constexpr int EXPLOSION_MIN_SIZE = 1; // Minimum particle size of the explosion
	constexpr int EXPLOSION_MAX_SIZE = 12; // Maximum particle size of the explosion
	constexpr double COEFF_CHANGE_COLOR = 0.5; // The time factor for changing the color of the explosion

    // Explosion color parameters
    constexpr uint32_t EXPLOSION_COLOR = Color::ORANGE; // The first color of the explosion
    constexpr uint32_t EXPLOSION_COLOR_2 = Color::RED; // The second color of the explosion

	// Game logic parameters
	constexpr double SUCCESSFUL_LANDED_HEIGHT = 4.0; // Maximum height for a successful landing
	constexpr double SUCCESSFUL_LANDED_ANGLE = 7.0; // Maximum angle deviation for a successful landing
	constexpr double SUCCESSFUL_LANDED_VELOCITY = 50.0; // Maximum speed for a successful landing
    constexpr int POINT_MODIFIER = 10; // The points modifier for a successful landing

	// Game session parameters
    constexpr int SLEEP_LEVEL_TIME = 200; // Waiting time in milliseconds between levels
    constexpr int SLEEP_PAUSE_TIME = 200; // Waiting time in milliseconds when paused
    


    // Difficulty Parameters
    const std::map<Difficulty, DifficultyParams> DIFFICULTY_CONFIG = {
    { Difficulty::Easy, {120.0, {1, 2}, "Easy", Color::Violet}},
    { Difficulty::Medium, {60.0, {1, 2, 3}, "Medium", Color::BLUE}},
    { Difficulty::Hard, {30.0, {2, 3}, "Hard", Color::PINK}},
    { Difficulty::Demon, {45.0, {2, 3}, "DEMON", Color::RED_2}}
    };

    // Common constants
    const Vector2 GRAVITY_ACCELERATION = { 0.0, GameData::GRAVITY };
    const std::vector<std::string> STRING_POINTS = {
                                                    "",
                                                    "+" + std::to_string(POINT_MODIFIER * 1),
                                                    "+" + std::to_string(POINT_MODIFIER * 2),
                                                    "+" + std::to_string(POINT_MODIFIER * 3)
                                                    };
};
