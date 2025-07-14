#pragma once

#include "Engine.h"

#include <vector>


#define PI 3.14159265358979323846
#define PIXELFONT_H 7
#define PIXELFONT_W 5


// ����� ��� �������� ���� ��������
namespace GameData {
    // ��������� ������
    constexpr double SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    constexpr double SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    // ��������� ������� ������
    constexpr double START_ROCKET_X = SCREEN_WIDTH / 2.0;
    constexpr double START_ROCKET_Y = 40.0;

    // ��������� ������
    constexpr double ROCKET_HEIGHT = 40.0;
    constexpr double ROCKET_WIDTH = 30.0;
    constexpr double WINDOW_RADIUS = 5.0;
    constexpr double WINDOW_OFFSET_Y = 0.0;

    // ��������� �������
    constexpr double FLAME_MAX_HEIGHT = 20.0;
    constexpr double FLAME_MAX_WIDTH = 15.0;

    // ���������� ���������
    constexpr double INITIAL_SPEED = 100.0;
    constexpr double GRAVITY = 50.0;
    constexpr double WINDOW_MARGIN_X = 20.0;
    constexpr double WINDOW_MARGIN_Y = 40.0;
    constexpr double ROTATION_SPEED = 3.0;       // �������� ��������
    constexpr double MAX_THRUST_FORCE = 200.0;   // ������������ ���� ����
    constexpr double THRUST_MIN_VAL = 0.01;
    constexpr double MAX_THRUST = 1.0;
    constexpr double THRUST_SPEED = 5.0;
	constexpr double FUEL_CONSUMPTION_RATE = 10; // ������ ������� � �������
    const std::vector<double> FUEL_MAX = { 120.0, 60.0, 30.0 }; // ������������ ���������� ������� (Easy, Medium, Hard)

    // �����
	constexpr uint32_t WHITE = 0xFFFFFFFF; // �����
	constexpr uint32_t BLACK = 0xFF000000; // ׸����
    constexpr uint32_t BLACK_2 = 0x80000000;  // �������������� ������
	constexpr uint32_t GRAY = 0xFF808080; // �����
    constexpr uint32_t DARK_GRAY = 0x80404040; // �����-�����
    constexpr uint32_t DARK_ORANGE_1 = 0xFF8B4500;  // Ҹ���� ���������
    constexpr uint32_t DARK_ORANGE_2 = 0xFFCD6600;  // ������� ����-���������
    constexpr uint32_t DARK_ORANGE_3 = 0xFFFF8C00;  // ���������� ����� ���������
    constexpr uint32_t ORANGE = 0xFFFFA500;  // ���������
    constexpr uint32_t DARK_ORANGE = 0xFFFFA500;  // �����-���������
    constexpr uint32_t DARK_BLUE = 0xFF0000FF; // �����
    constexpr uint32_t GREEN = 0xFF00FF00; // ������� ����
    constexpr uint32_t RED_1 = 0xFFFF0000;    // ����-������� 
    constexpr uint32_t RED_2 = 0xFFDC143C;    // ��������� 
    constexpr uint32_t RED_3 = 0xFFB22222;    // �������-������� 
    constexpr uint32_t DARK_RED = 0xFF8B0000;    // Ҹ���-������� 



    constexpr uint32_t ROCKET_COLOR = DARK_BLUE; // �����
    constexpr uint32_t WINDOW_COLOR = WHITE; // �����
    constexpr uint32_t FLAME_COLOR = ORANGE;  // ���������


    // ��������� ������ �����������
    constexpr int MOON_MIN_HEIGHT_MAP = 100;  // ����������� ������ �����������
    constexpr int MOON_MAX_HEIGHT_MAP = 400;  // ������������ ������ �����������
	constexpr int MOON_MIN_HEIGHT_MOUNTAIN = 50; // ����������� ������ ����
	constexpr int MOON_MIN_LENGTH = 5; // ����������� ����� ������� �����������
    constexpr int MOON_MAX_LENGTH = 10; // ������������ ����� ������� �����������
	constexpr int MOON_MIN_HEIGHT = 5; // ����������� ������ ������� �����������
    constexpr int MOON_MAX_HEIGHT = 10; // ������������ ������ ������� �����������
	constexpr int MOON_LENGTH_X1 = 120; // ����� ������ � ������������� ����� x1
    constexpr int MOON_LENGTH_X2 = 60; // ����� ������ � ������������� ����� x2
    constexpr int MOON_LENGTH_X3 = 40; // ����� ������ � ������������� ����� x3
    constexpr int MAX_ALLOWED_STRAIGHT_X = SCREEN_WIDTH - MOON_LENGTH_X1;
    constexpr uint32_t MOON_COLOR = 0xFFFFFFFF; // ����� ���� �����������
	constexpr uint32_t MOON_LANDING_COLOR = GREEN; // ������� ���� ��� ���������� �������
	constexpr uint32_t POINTS_INFO_COLOR = DARK_BLUE; // ����� ���� ��� ���������� � �����
	constexpr int POINTS_INFO_MARGIN_Y = 15; // ������ �� Y ��� ���������� � �����


    // ����� � ��������� ����������
    constexpr uint32_t HUD_TEXT_COLOR = WHITE; // �����
    constexpr uint32_t HUD_BG_COLOR = BLACK_2;  // �������������� ������
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


    // ��������� ��� ������
    constexpr int EXPLOSION_PARTICLES_COUNT = 50; // ���������� ������ ������
    constexpr double EXPLOSION_DURATION = 1.0; // ������������ ������ � ��������
    constexpr double EXPLOSION_MIN_SPEED = 50.0; // ����������� �������� ������ ������
	constexpr double EXPLOSION_MAX_SPEED = 150.0; // ������������ �������� ������ ������
	constexpr int EXPLOSION_MAX_SIZE = 12; // ������������ ������ ������ ������
    constexpr int EXPLOSION_MIN_SIZE = 1; // ����������� ������ ������ ������
    constexpr uint32_t EXPLOSION_COLOR = ORANGE; // ���� ������
	constexpr uint32_t EXPLOSION__COLOR_2 = RED_3; // ��������� ���� ������
	constexpr double COEFF_CHANGE_COLOR = 0.5; // ����������� ��������� ����� ������
};
