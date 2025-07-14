#pragma once

#include "Engine.h"

#include <vector>


#define PI 3.14159265358979323846
#define PIXELFONT_H 7
#define PIXELFONT_W 5


// Класс для хранения всех констант
namespace GameData {
    // Константы экрана
    constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // Стартовая позиция ракеты
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = 40.0;

    // Параметры ракеты
    constexpr double ROCKET_HEIGHT = 40.0;
    constexpr double ROCKET_WIDTH = 30.0;
    constexpr double WINDOW_RADIUS = 5.0;
    constexpr double WINDOW_OFFSET_Y = 0.0;

    // Параметры пламени
    constexpr double FLAME_MAX_HEIGHT = 20.0;
    constexpr double FLAME_MAX_WIDTH = 15.0;

    // Физические параметры
    constexpr double INITIAL_SPEED = 100.0;
    constexpr double GRAVITY = 50.0;
    constexpr double WINDOW_MARGIN_X = 20.0;
    constexpr double WINDOW_MARGIN_Y = 40.0;
    constexpr double ROTATION_SPEED = 3.0;       // Скорость поворота
    constexpr double MAX_THRUST_FORCE = 200.0;   // Максимальная сила тяги
    constexpr double THRUST_MIN_VAL = 0.01;
    constexpr double MAX_THRUST = 1.0;
    constexpr double THRUST_SPEED = 5.0;
	constexpr double FUEL_CONSUMPTION_RATE = 10; // Расход топлива с секунду
    const std::vector<double> FUEL_MAX = { 120.0, 60.0, 30.0 }; // Максимальное количество топлива (Easy, Medium, Hard)

    // Цвета
	constexpr uint32_t WHITE = 0xFFFFFFFF; // Белый
	constexpr uint32_t BLACK = 0xFF000000; // Чёрный
    constexpr uint32_t BLACK_2 = 0x80000000;  // Полупрозрачный чёрный
	constexpr uint32_t GRAY = 0xFF808080; // Серый
    constexpr uint32_t DARK_GRAY = 0x80404040; // темно-серый
    constexpr uint32_t DARK_ORANGE_1 = 0xFF8B4500;  // Тёмный оранжевый
    constexpr uint32_t DARK_ORANGE_2 = 0xFFCD6600;  // Средний тёмно-оранжевый
    constexpr uint32_t DARK_ORANGE_3 = 0xFFFF8C00;  // Насыщенный тёмный оранжевый
    constexpr uint32_t ORANGE = 0xFFFFA500;  // Оранжевый
    constexpr uint32_t DARK_ORANGE = 0xFFFFA500;  // темно-оранжевый
    constexpr uint32_t DARK_BLUE = 0xFF0000FF; // Синий
    constexpr uint32_t GREEN = 0xFF00FF00; // Зеленый цвет
    constexpr uint32_t RED_1 = 0xFFFF0000;    // Ярко-красный 
    constexpr uint32_t RED_2 = 0xFFDC143C;    // Карминный 
    constexpr uint32_t RED_3 = 0xFFB22222;    // Огненно-красный 
    constexpr uint32_t DARK_RED = 0xFF8B0000;    // Тёмно-красный 



    constexpr uint32_t ROCKET_COLOR = DARK_BLUE; // Синий
    constexpr uint32_t WINDOW_COLOR = WHITE; // Белый
    constexpr uint32_t FLAME_COLOR = ORANGE;  // Оранжевый


    // Параметры лунной поверхности
    constexpr int MOON_MIN_HEIGHT_MAP = 100;  // Минимальная высота поверхности
    constexpr int MOON_MAX_HEIGHT_MAP = 400;  // Максимальная высота поверхности
	constexpr int MOON_MIN_HEIGHT_MOUNTAIN = 50; // Минимальная высота горы
	constexpr int MOON_MIN_LENGTH = 5; // Минимальная длина участка поверхности
    constexpr int MOON_MAX_LENGTH = 10; // Максимальная длина участка поверхности
	constexpr int MOON_MIN_HEIGHT = 5; // Минимальная высота участка поверхности
    constexpr int MOON_MAX_HEIGHT = 10; // Максимальная высота участка поверхности
	constexpr int MOON_LENGTH_X1 = 120; // Длина учатка с коэффициентом очков x1
    constexpr int MOON_LENGTH_X2 = 60; // Длина учатка с коэффициентом очков x2
    constexpr int MOON_LENGTH_X3 = 40; // Длина учатка с коэффициентом очков x3
    constexpr int MAX_ALLOWED_STRAIGHT_X = SCREEN_WIDTH - MOON_LENGTH_X1;
    constexpr uint32_t MOON_COLOR = 0xFFFFFFFF; // Белый цвет поверхности
	constexpr uint32_t MOON_LANDING_COLOR = GREEN; // Зеленый цвет для безопасной посадки
	constexpr uint32_t POINTS_INFO_COLOR = DARK_BLUE; // Синий цвет для информации о очках
	constexpr int POINTS_INFO_MARGIN_Y = 15; // Отступ по Y для информации о очках


    // Цвета и параметры интерфейса
    constexpr uint32_t HUD_TEXT_COLOR = WHITE; // Белый
    constexpr uint32_t HUD_BG_COLOR = BLACK_2;  // Полупрозрачный чёрный
    constexpr int HUD_PADDING_LEFT_X = 30;
	constexpr int HUD_PADDING_LEFT_Y = 30;
	constexpr int HUD_PADDING_RIGHT_X = SCREEN_WIDTH - 250;
	constexpr int HUD_PADDING_RIGHT_Y = 30;
    constexpr int HUD_FONT_SIZE = 30;
    constexpr int HUD_BAR_WIDTH = 100;
    constexpr int HUD_BAR_HEIGHT = 10;
    constexpr uint32_t HUD_BAR_EMPTY_COLOR = GRAY;
    constexpr uint32_t HUD_BAR_COLOR = GREEN;
	constexpr double HUD_VAL_SCALE = 0.1;


    // Константы для взрыва
    constexpr int EXPLOSION_PARTICLES_COUNT = 50; // Количество частиц взрыва
    constexpr double EXPLOSION_DURATION = 1.0; // Длительность взрыва в секундах
    constexpr double EXPLOSION_MIN_SPEED = 50.0; // Минимальная скорость частиц взрыва
	constexpr double EXPLOSION_MAX_SPEED = 150.0; // Максимальная скорость частиц взрыва
	constexpr int EXPLOSION_MAX_SIZE = 12; // Максимальный размер частиц взрыва
    constexpr int EXPLOSION_MIN_SIZE = 1; // Минимальный размер частиц взрыва
    constexpr uint32_t EXPLOSION_COLOR = ORANGE; // Цвет взрыва
	constexpr uint32_t EXPLOSION__COLOR_2 = RED_3; // Вторичный цвет взрыва
	constexpr double COEFF_CHANGE_COLOR = 0.5; // Коэффициент изменения цвета взрыва
};
