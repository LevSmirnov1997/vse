#pragma once
#include <iostream>
#include "al/math/mat_utils.hpp"


class Transform 
{
public:
	void move(const float x, const float y)
	{
		m_pos = mat_utils::translate(m_pos, vec2(x, y));
	}

	void scale(const float x, const float y)
	{
		m_pos = mat_utils::scale(m_pos, vec2(x, y));
	}

	void rotate(const float fi)
	{
		m_pos = mat_utils::rotate(m_pos, fi);
		for (int i = 0; i < 16; ++i)
			std::cout << m_pos.get_values()[i];
	}

	const mat4 get_data(void) const
	{
		return m_pos;
	}

	Transform() = default;

private:

	mat4 m_pos;
};