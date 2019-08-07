#pragma once

struct vec2
{
    float x;
    float y;

    vec2();
    vec2(float x, float y);
    vec2 operator+(const vec2 &rhs) const; //Adding vectors
    vec2 operator-(const vec2 &rhs) const; //Subtracting vectors
	vec2 operator+=(const vec2 &rhs);
	vec2 operator-=(const vec2 &rhs);
};

float magn(const vec2 &v); //Magnitude of vector
float dot(const vec2 &lhs, const vec2 &rhs); //Dot product of vectors
vec2 dot(const vec2 &lhs, float rhs); //Dot product of vector & scalar
float cross(const vec2 &lhs, const vec2 &rhs); //Cross product of vectors
