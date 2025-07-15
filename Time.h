#pragma once


// класс времени для отслеживания игрового времени
struct Time {
    inline static double time = 0.0;

    static void AddTime(double t) {
        time += t;
    }

    static void Reset() {
        time = 0.0;
    }
};

