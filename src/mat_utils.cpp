#include <mat_utils.hpp>
#include <algorithm>
#include <cmath>

mat4 scale(const mat4& transf, const vec2& sc) {
    float t_arr[16];
    std::fill_n(t_arr, 16, 0);
    t_arr[0] = sc.get_x();
    t_arr[5] = sc.get_y();
    t_arr[10] = 1.0f;
    t_arr[15] = 1.0f;
    return (mult(mat4(t_arr), transf));
}

mat4 rotate(const mat4& transf, float rt) {
    float t_arr[16];
    std::fill_n(t_arr, 16, 0);
    for(int i = 0; i < 4; ++i)
        t_arr[5*i] = 1;
    t_arr[0] = cos(rt * 3.141592653 / 180);
    t_arr[1] = -sin(rt * 3.141592653 / 180);
    t_arr[4] = sin(rt * 3.141592653 / 180);
    t_arr[5] = cos(rt * 3.141592653 / 180);
    return (mult(mat4(t_arr), transf));
}

mat4 translate(const mat4& transf, const vec2& tr) {
    float t_arr[16];
    std::fill_n(t_arr, 16, 0);
    for(int i = 0; i < 4; ++i)
        t_arr[5*i] = 1;
    t_arr[3] = tr.get_x();
    t_arr[7] = tr.get_y();
    t_arr[11] = 1.0f;
    return (mult(mat4(t_arr), transf));
}
