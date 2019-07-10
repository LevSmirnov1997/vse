#pragma once

#include "vec2.hpp"
#include "mat4.hpp"
#include <limits>

namespace math
{
	/*
	 * Rotate a matrix @t for @rt degrees around the @around point.
	 * If @around is not specified rotates around itself.
	*/
	mat4 rotate(const mat4& t, float rt, vec2 around = { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() });

	/* Convert degrees to radians */
	float radians(float degrees);

	/* Convert radians to degrees */
	float degrees(float radians);

	vec2 truncate(vec2 value, vec2 limit);

	vec2 normalize(vec2 v);

	mat4 scale(const mat4& t, const vec2& sc);
	mat4 translate(const mat4& transf, const vec2& tr);
	mat4 mult(const mat4& lhs, const mat4& rhs);
	vec2 mult(const mat4 &lhs, const vec2 &rhs);
	mat4 ortho(float left, float right, float bottom, float top, float near, float far);
}
