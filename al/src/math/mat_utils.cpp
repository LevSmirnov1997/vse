#include "mat_utils.hpp"
#include <algorithm>
#include <cmath>
constexpr float PI = 3.141592653f;

mat4 math::scale(const mat4& transf, const vec2& sc) {
	float t_arr[16] = {0.0f};
	t_arr[0] = sc.x;
	t_arr[5] = sc.y;
	t_arr[10] = 1.0f;
	t_arr[15] = 1.0f;
	return math::mult(transf, mat4(t_arr));
}

mat4 math::rotate(const mat4& transf, float rt, vec2 around) {
	float x, y;
	if (around.x == std::numeric_limits<float>::infinity()) {
		x = transf.get_values()[3];
		y = transf.get_values()[7];
	}
	else {
		x = around.x;
		y = around.y;
	}
	float t_arr[16] = {0.0f};
	for (int i = 0; i < 4; ++i)
		t_arr[5 * i] = 1;
	t_arr[0] = cos(rt * PI / 180);
	t_arr[1] = -sin(rt * PI / 180);
	t_arr[4] = sin(rt * PI / 180);
	t_arr[5] = cos(rt * PI / 180);
	return math::translate(math::mult(mat4(t_arr), math::translate(transf, vec2(-x, -y))), vec2(x, y));
}

mat4 math::translate(const mat4& transf, const vec2& tr) {
	float t_arr[16] = {0.0f};
	for (int i = 0; i < 4; ++i)
		t_arr[5 * i] = 1;
	t_arr[3] = tr.x;
	t_arr[7] = tr.y;
	return math::mult(mat4(t_arr), transf);
}

mat4 math::mult(const mat4& lhs, const mat4& rhs) {
	float t_arr[16] = {0.0f};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				t_arr[4 * i + j] += lhs.get_values()[4 * i + k] * rhs.get_values()[4 * k + j];
			}
		}
	}
	return {t_arr};
}

vec2 math::mult(const mat4 &lhs, const vec2 &rhs)
{
	float f[2] { rhs.x, rhs.y };
	const float *m = lhs.get_values();
	return {
		(m[0]*f[0] + m[1]*f[1] + m[2] + m[3]),
		(m[4]*f[0] + m[5]*f[1] + m[6] + m[7])
	};
}

mat4 math::ortho(float left, float right, float bottom, float top, float near, float far)
{
	float projection[16] = { 0.0f };
	projection[0] = 2.0f / (right - left);
	projection[5] = 2.0f / (top - bottom);
	projection[10] = -2.0f / (far - near);
	projection[3] = -(right + left) / (right - left);
	projection[7] = -(top + bottom) / (top - bottom);
	projection[11] = -(far + near) / (far - near);
	projection[15] = 1.0f;
	return { projection };
}

float math::radians(float degrees)
{
	return degrees * (PI / 180.f);
}

float math::degrees(float radians)
{
	return radians * (180.f / PI);
}

vec2 math::truncate(vec2 value, vec2 limit)
{
	vec2 res = value;
	if (value.x > limit.x)
	{
		res.x = limit.x;
	}
	else if(value.x < -limit.x)
	{
		res.x = -limit.x;
	}

	if(value.y > limit.y)
   	{
		res.y = limit.y;
	}
	else if(value.y < -limit.y)
   	{
		res.y = -limit.y;
	}
	return res;
}

vec2 math::normalize(vec2 v)
{
	float x = v.x;
	float y = v.y;
	float den = std::sqrt(x*x + y * y);
	return { x / den, y / den };
}

bool math::inverse(const mat4 &in, mat4 &out)
{
    const float *m = in.get_values();
    float inv[16];
    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;
    det /= 1.0;

    for (int i = 0; i < 16; ++i)
        inv[i] *= det;

    out = { inv };
    return true;
}

