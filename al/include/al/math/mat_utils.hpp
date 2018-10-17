#pragma once

#include "vec2.hpp"
#include "mat4.hpp"

namespace math
{
	mat4 scale(const mat4& transf, const vec2& sc);
	mat4 rotate(const mat4& transf, float rt);
	mat4 translate(const mat4& transf, const vec2& tr);
	mat4 mult(const mat4& lhs, const mat4& rhs);
}