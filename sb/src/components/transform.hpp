#pragma once
#include <al/math/mat4.hpp>


class transform 
{
public:

	transform() = default;

	transform(float mat[16]) :m_pos(mat4(mat)) {};

	mat4 m_pos;
};