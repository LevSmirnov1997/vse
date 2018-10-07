#include "mat4.hpp"
#include <algorithm>

mat4::mat4() {
    std::fill_n(values, 16, 0);
}

mat4::mat4(float x) {
    std::fill_n(values, 16, 0);
    values[0] = values[5] = values[10] = values[15] = x;
}

mat4::mat4(float arr[16]) {
    std::copy(arr, arr + 16, values);
}

mat4 mult(const mat4& lhs, const mat4& rhs) {
    float t_arr[16];
    std::fill_n(t_arr, 16, 0);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 4; ++k) {
                t_arr[4*i+j] += lhs.get_values()[4*i+k] * rhs.get_values()[4*k+j];
            }
        }
    }
    return mat4(t_arr);
}
