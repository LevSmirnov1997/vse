#pragma once
#include <al/math/mat4.hpp>
#include <al/math/vec2.hpp>

struct transform 
{
	mat4 transf;
    float angle = 0.f;
	vec2 velocity = { 0.f, 0.f };
	float max_speed = 25.f;
	float mass = 10.f;
};
