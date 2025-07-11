#pragma once

#include "Engine.h"


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

    // �����
    constexpr uint32_t ROCKET_COLOR = 0xFF0000FF; // �����
    constexpr uint32_t WINDOW_COLOR = 0xFFFFFFFF; // �����
    constexpr uint32_t FLAME_COLOR = 0xFFFFA500;  // ���������

    // ��������� ������ �����������
    //constexpr int MOON_SEGMENTS = 20;          // ���������� ��������� �����������
	//constexpr double MOON_MIN_POINTS_COUNT = 20; // ����������� ���������� ����� �� ����������� ����
	//constexpr double MOON_MAX_POINTS_COUNT = 20; // ������������ ���������� ����� �� ����������� ����
	constexpr double MOON_MIN_STRAIGHT_SEGMENTS_COUNT = 3; // ����������� ���������� ������ ���������
	constexpr double MOON_MAX_STRAIGHT_SEGMENTS_COUNT = 3; // ������������ ���������� ������ ���������
    constexpr double MOON_MIN_HEIGHT_MAP = 100.0;  // ����������� ������ �����������
    constexpr double MOON_MAX_HEIGHT_MAP = 400.0;  // ������������ ������ �����������
	constexpr double MOON_MIN_LENGTH = 10.0; // ����������� ����� ������� �����������
    constexpr double MOON_MAX_LENGTH = 20.0; // ������������ ����� ������� �����������
	constexpr double MOON_MIN_HEIGHT = 5.0; // ����������� ������ ������� �����������
    constexpr double MOON_MAX_HEIGHT = 25.0; // ������������ ������ ������� �����������
	constexpr double MOON_LENGTH_X1 = 120.0; // ����� ������ � ������������� ����� x1
    constexpr double MOON_LENGTH_X2 = 60.0; // ����� ������ � ������������� ����� x2
    constexpr double MOON_LENGTH_X3 = 40.0; // ����� ������ � ������������� ����� x3
    constexpr uint32_t MOON_COLOR = 0xFFFFFFFF; // ����� ���� �����������

    // ����� � ��������� ����������
    constexpr uint32_t HUD_TEXT_COLOR = 0xFFFFFFFF; // �����
    constexpr uint32_t HUD_BG_COLOR = 0x80000000;  // �������������� ������
    constexpr int HUD_PADDING = 10;
    constexpr int HUD_FONT_SIZE = 20;
};
