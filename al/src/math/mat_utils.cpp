#include "mat_utils.hpp"
#include <algorithm>
#include <cmath>
constexpr float PI = 3.141592653f;

mat4 math::scale(const mat4& transf, const vec2& sc) {
	float t_arr[16] = {0.0f};
	t_arr[0] = sc.get_x();
	t_arr[5] = sc.get_y();
	t_arr[10] = 1.0f;
	t_arr[15] = 1.0f;
	return math::mult(transf, mat4(t_arr));
}

mat4 math::rotate(const mat4& transf, float rt, vec2 around) {
	float x, y;
	if (around.get_x() == std::numeric_limits<float>::infinity()) {
		x = transf.get_values()[3];
		y = transf.get_values()[7];
	}
	else {
		x = around.get_x();
		y = around.get_y();
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
	t_arr[3] = tr.get_x();
	t_arr[7] = tr.get_y();
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
	float f[2] { rhs.get_x(), rhs.get_y() };
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
	if (value.get_x() > limit.get_x())
	{
		res.set_x(limit.get_x());
	}
	else if(value.get_x() < -limit.get_x())
	{
		res.set_x(-limit.get_x());
	}

	if(value.get_y() > limit.get_y())
   	{
		res.set_y(limit.get_y());
	}
	else if(value.get_y() < -limit.get_y())
   	{
		res.set_y(-limit.get_y());
	}
	return res;
}

vec2 math::normalize(vec2 v)
{
	float x = v.get_x();
	float y = v.get_y();
	float den = std::sqrt(x*x + y * y);
	return { x / den, y / den };
}
