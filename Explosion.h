#pragma once

#include "Vector2.h"

#include <vector>



class Explosion {
private:
    static bool isActive;         // ������� �� �����
    static double duration;        // ����� ����������������� ������
    static double currentTime;     // ������� ����� ������
    static Vector2 position;      // ������� ������ (�����)
    static std::vector<Vector2> particles; // ������� ������
    static std::vector<Vector2> velocities; // �������� ������

public:
    static void Start(const Vector2& pos);
    static void Update(double dt);
    static void Draw();
    static bool IsActive() { return isActive; }
    static void Finish();
};
