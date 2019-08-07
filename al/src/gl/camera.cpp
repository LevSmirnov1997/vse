#include "camera.hpp"

camera::camera(int width, int height)
	: m_w(width), m_h(height), m_scale(0.f), m_position()
{
	this->update();
}

void camera::scale(float zoom)
{
	m_scale += zoom;
	this->update();
}

void camera::resize(int w, int h)
{
	m_w = w;
	m_h = h;
	this->update();
}

void camera::move(vec2 offset)
{
	const float tuning = 1.2f;
	float coef = 1.0;
	if (m_scale > 0)
	{
		coef = tuning * (m_h + m_scale) / (float)m_h;
	}
	else if (m_scale < 0)
	{
		coef = 1 / (tuning * (float)m_h / (m_h + m_scale));
	}
	offset = { offset.x * coef, offset.y * coef };
	m_position += offset;
	this->update();
}

void camera::update()
{
	float x = -m_position.x;
	float y = -m_position.y;
	float scale_x = m_scale * (m_w / (float)m_h);
	float scale_y = m_scale;
	m_view = math::ortho(x-scale_x, m_w + x + scale_x, m_h + y + scale_y, y-scale_y, -1, 1);
}

vec2 camera::world_to_view(vec2 pos) const
{
	float scale_x = m_scale * (m_w / (float)m_h);
	float x = pos.x;
	float y = pos.y;

	return {
		x * ((m_w + 2.f*scale_x) / m_w) - scale_x - m_position.x,
		y * ((m_h + 2.f*m_scale) / m_h) - m_scale - m_position.y
	};
}
