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
