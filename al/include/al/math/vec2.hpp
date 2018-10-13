#pragma once

class vec2 {
private:
    float _x = 0, _y = 0;

public:
    vec2() = default;
    vec2(float x, float y);
    vec2(const vec2&) = default;
    ~vec2() = default;

    float get_x() const { return _x; };
    float get_y() const { return _y; };
    
    void set_x(float x) { this->_x = x; };
    void set_y(float y) { this->_y = y; };
    
    vec2 operator+(const vec2 &rhs) const; //Adding vectors
    vec2 operator-(const vec2 &rhs) const; //Subtracting vectors
    float magn() const; //Magnitude of vector
};

float dot(const vec2 &lhs, const vec2 &rhs); //Dot product of vectors
vec2 dot(const vec2 &lhs, float rhs); //Dot product of vector & scalar    
float cross(const vec2 &lhs, const vec2 &rhs); //Cross product of vectors
