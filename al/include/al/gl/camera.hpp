#pragma once
#include <al/math.hpp>

class camera
{
public:
	camera(int width, int height);

	void scale(float zoom);

	void resize(int width, int height);

	void move(vec2 offset);

	mat4 get() const { return m_view; }

	float get_scale() const { return m_scale; }

	vec2 get_view_size() const { return { (float)m_w, (float)m_h }; }

	vec2 get_view_pos() const { return m_position; }

	vec2 world_to_view(vec2 pos) const;

private:
	void update();

	mat4 m_view;
	int m_w, m_h;
	float m_scale;
	vec2 m_position;
};
