#include "mat_utils.hpp"
#include <algorithm>
#include <cmath>
constexpr float PI = 3.141592653f;

mat4 scale(const mat4& transf, const vec2& sc) {
    float t_arr[16] = {0.0f};
    t_arr[0] = sc.get_x();
    t_arr[5] = sc.get_y();
    t_arr[10] = 1.0f;
    t_arr[15] = 1.0f;
    return mult(mat4(t_arr), transf);
}

mat4 rotate(const mat4& transf, float rt) {
    float t_arr[16] = {0.0f};
    for(int i = 0; i < 4; ++i)
        t_arr[5*i] = 1;
    t_arr[0] = cos(rt * PI / 180);
    t_arr[1] = -sin(rt * PI / 180);
    t_arr[4] = sin(rt * PI / 180);
    t_arr[5] = cos(rt * PI / 180);
    return mult(mat4(t_arr), transf);
}

mat4 translate(const mat4& transf, const vec2& tr) {
    float t_arr[16] = {0.0f};
    for(int i = 0; i < 4; ++i)
        t_arr[5*i] = 1;
    t_arr[3] = tr.get_x();
    t_arr[7] = tr.get_y();
    t_arr[11] = 1.0f;
    return mult(mat4(t_arr), transf);
}

mat4 mult(const mat4& lhs, const mat4& rhs) {
    float t_arr[16] = {0.0f};
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 4; ++k) {
                t_arr[4*i+j] += lhs.get_values()[4*i+k] * rhs.get_values()[4*k+j];
            }
        }
    }
    return {t_arr};
}
