#pragma once
#include <al/math/mat4.hpp>
#include <al/math/mat_utils.hpp>
#include <cmath>
const float PI = 3.141592653f;

struct transform 
{
	mat4 transf;
    float angle = 0;
    void move(float step)
    {
        float rad = angle * PI / 180.0f;
        float x = (step * sin(rad));
        float y = -fabs(step * cos(rad));
        if (cos(rad) < 0)
            y = -y;
        if (step < 0)
            y = -y;
        transf = math::translate(transf, vec2(x, y));
    }

    void rotate(float degr)
    {
        angle += degr;
        transf = math::rotate(transf, degr);
    }
};
