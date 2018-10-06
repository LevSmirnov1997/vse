#pragma once

class mat4 {
private:
    float values [16];
public:
    mat4();
    mat4(float x);
    mat4(float arr[16]);
    ~mat4() = default;

    const float *const get_values() const { return values; }
};
