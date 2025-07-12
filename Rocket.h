#pragma once

#include "GameData.h"
#include "Vector2.h"


// ����� ������ (��������)
class Rocket {
private:
    static Vector2 position;      // ������� ������
    static Vector2 direction;     // ������ ����������� ������ (�� ������ � ����)
    static Vector2 velocity;      // �������� ������
    static Vector2 acceleration;  // ��������� ������
    static double angle;          // ������� ���� �������� (���)
    static double altitudeAboveMoon;         // ������ ������ ��� ������������ ����
    static double flameSize;      // ������ ������� (0..1)
    static double thrust;         // ���� ���� (0..1)
    
public:
    static Vector2 GetVelocity() { return velocity; }
	static Vector2 GetPosition() { return position; }
	static Vector2 GetDirection() { return direction; }
    static double GetAltitude() { return altitudeAboveMoon; }
    static double GetThrust() { return thrust; }
    static double GetAngleDegrees();

public:
    static void Initialize(); // ������������� ������

    static void Update(double dt); // ���������� ��������� ������

    static void Draw(); // ��������� ������

private:
    Rocket() = delete;

    static void UpdateRotation(double dt); // ���������� ���� �������� ������
    static void UpdateThrust(double dt); // ���������� ���� ������
    static void ApplyPhysics(double dt); // ���������� ������ � ������
    static void DrawRocketBody(); // ��������� ���� ������
    static void DrawRocketWindow(); // ��������� ���� ������
    static void DrawRocketFlame(); // ��������� ������� ������
};
