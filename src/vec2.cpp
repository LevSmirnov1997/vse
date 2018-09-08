#include "vec2.hpp"
#include <cmath>

vec2::vec2(float x, float y) :_x(x), _y(y) {}

vec2 vec2::operator+(const vec2 &rhs) const {
    return vec2(_x + rhs.get_x(), _y + rhs.get_y());
}

vec2 vec2::operator-(const vec2 &rhs) const {
    return vec2(_x - rhs.get_x(), _y - rhs.get_y());
}

float vec2::magn() const {
    return sqrt(pow(_x, 2.0) + pow(_y, 2.0));
}

float dot(const vec2 &lhs, const vec2 &rhs) {
    return (lhs.get_x() * rhs.get_x() + lhs.get_y() * rhs.get_y());
}

vec2 dot(const vec2 &lhs, float rhs) {
    return vec2(lhs.get_x() * rhs, lhs.get_y() * rhs);
}

float cross(const vec2 &lhs, const vec2 &rhs) {
    return (lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x());
}
