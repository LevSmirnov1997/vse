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
	return math::mult(mat4(t_arr), transf);
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

mat4 math::ortho(float left, float right, float bottom, float top, float near, float far)
{
	float projection[16] = { 0.0f };
	projection[0] = 2.0 / (right - left);
	projection[5] = 2.0 / (top - bottom);
	projection[10] = -2.0 / (far - near);
	projection[3] = -(right + left) / (right - left);
	projection[7] = -(top + bottom) / (top - bottom);
	projection[11] = -(far + near) / (far - near);
	projection[15] = 1.0f;
	return { projection };
}
