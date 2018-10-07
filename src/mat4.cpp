#include "vse/mat4.hpp"
#include <algorithm>

mat4::mat4() :values{0.0f} {
    values[0] = values[5] = values[10] = values[15] = 1.0f;
}

mat4::mat4(float arr[16]) {
    std::copy(arr, arr + 16, values);
}
