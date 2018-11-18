#pragma once
#include <al/math.hpp>

class camera
{
public:
	camera(int width, int height);

	void zoom(float zoom);

	void resize(int width, int height);

	void move(vec2 offset);

	mat4 get() const { return m_view; }

private:
	void update();

	mat4 m_view;
	vec2 m_position;
	float m_scale;
	int m_w, m_h;
};
