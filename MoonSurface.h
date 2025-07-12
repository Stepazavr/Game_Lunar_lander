#pragma once

#include "GameData.h"
#include "Vector2.h"

#include <vector>


class MoonSurface {
private:
    static std::vector<Vector2> surfacePoints;
    static bool stop_generate;

public:
    static void Generate();

    static void Draw();

    // �������� �������� ������ � ������������
    static bool CheckCollision(const Vector2& rocketPos, const Vector2& rocketDir, int& surfaceIndex);

    // ��������� ������ ������ ��� ������������ ����
    static double GetAltitudeAboveMoon(const Vector2& rocketPos);


private:
    static int GetSurfaceIndex(const Vector2& A, const Vector2& B);
    static bool IsPointUnderSurface(const Vector2& point);
    static void GenerateLeftPartOfMauntain(double h_max);   // ��������� ����� ����� ���� (����������)
    static void GenerateRightPartOfMauntain(double h_min);  // ��������� ������ ����� ���� (����)
    static void GenerateStraightPartOfMauntain();           // ��������� ������� ������� ����
    static std::pair<Vector2, Vector2> GetSurfaceUnderRocket(const Vector2& rocketPos);

    static double Rand_length();
    static double Rand_height();
};