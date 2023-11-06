#pragma once

#include <iostream>

using namespace std;

struct Vector2f
{
    Vector2f() : x(0.0), y(0.0) {}
    Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
    Vector2f(float p) : x(p), y(p) {}

    void print()
    {
        cout << "x: " << x << ", y: " << y << endl;
    }

    float x; float y;
};