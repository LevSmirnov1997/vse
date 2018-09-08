#include "vec2.hpp"
#include <cmath>

//Vector calculations
vec2 vec2::operator+(const vec2 &rhs) const {
    return vec2(_x + rhs.getX(), _y + rhs.getY());
}

vec2 vec2::operator*(float lhs, const vec2 &rhs) {
    return vec2(lhs * rhs.getX(), lhs * rhs.getY());
}

vec2 vec2::operator*(const vec2 &lhs, float rhs) {
    return (rhs * lhs);
}

float vec2::cross(const vec2 &v) const {
    return _x * v.getY() - _y * v.getX();
}

float vec2::magn() const {
    return sqrt(pow(_x, 2.0) + pow(_y, 2.0));
}

vec2 operator*(float lhs, const vec2 &rhs) {
    return vec2(lhs * rhs.getX(), lhs * rhs.getY());
}

vec2 operator*(const vec2 &lhs, float rhs) {
    return (rhs * lhs);
}
