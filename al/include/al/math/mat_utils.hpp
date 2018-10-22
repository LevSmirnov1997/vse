#pragma once

#include "vec2.hpp"
#include "mat4.hpp"
#include <limits>

namespace math
{
	/*
	 Rotate a matrix @t for @rt degrees around the @around point.
	 If @around is not specified rotates around itself.
	*/
	mat4 rotate(const mat4& t, float rt, vec2 around = { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() });
	mat4 scale(const mat4& t, const vec2& sc);
	mat4 translate(const mat4& transf, const vec2& tr);
	mat4 mult(const mat4& lhs, const mat4& rhs);
	mat4 ortho(float left, float right, float bottom, float top, float near, float far);
}
