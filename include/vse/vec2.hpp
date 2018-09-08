//#pragma once //OR
#ifndef VEC2_HPP
#define VEC2_HPP

class vec2 {
private:
    float _x = 0, _y = 0;

public:
    vec2() = default;
    vec2(const vec2&) = default;
    ~vec2() = default;

    float get_x() const { return _x; };
    float get_y() const { return _y; };
    
    void set_x(float x) { this->_x = x; };
    void set_y(float y) { this->_y = y; };
    
    vec2 operator+(const vec2 &rhs) const;//Adding vectors
    vec2 operator-(const vec2 &rhs) const;//Subtracting vectors
    float operator*(const vec2 &rhs) const;//Dot product of vectors
    float cross(const vec2 &v) const;//Cross product of vectors
    float magn() const;//Magnitude of vector

    friend vec2 operator*(float lhs, const vec2 &rhs);//Dot product scalar * vector    
    friend vec2 operator*(const vec2 &lhs, float rhs);//Dot product vector * scalar
};

#endif
