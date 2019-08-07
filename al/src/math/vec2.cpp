#include "vec2.hpp"
#include <cmath>

vec2::vec2()
    : x(0.f), y(0.f)
{
}

vec2::vec2(float x, float y)
    : x(x), y(y)
{
}

vec2 vec2::operator+(const vec2 &rhs) const
{
    return { x + rhs.x, y + rhs.y };
}

vec2 vec2::operator-(const vec2 &rhs) const
{
    return { x - rhs.x, y - rhs.y };
}

vec2 vec2::operator+=(const vec2 &rhs)
{
	*this = *this + rhs;
	return *this;
}

vec2 vec2::operator-=(const vec2 &rhs)
{
	*this = *this - rhs;
	return *this;
}

float magn(const vec2 &v)
{
    return sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
}

float dot(const vec2 &lhs, const vec2 &rhs)
{
    return (lhs.x * rhs.x + lhs.y * rhs.y);
}

vec2 dot(const vec2 &lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };
}

float cross(const vec2 &lhs, const vec2 &rhs)
{
    return (lhs.x * rhs.y - lhs.y * rhs.x);
}
