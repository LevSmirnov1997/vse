#include "camera.hpp"

camera::camera(int width, int height)
	: m_w(width), m_h(height), m_scale(0.f), m_position(0, 0)
{
	this->update();
}

void camera::zoom(float zoom)
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
	offset = { offset.get_x() * coef, offset.get_y() * coef };
	m_position += offset;
	this->update();
}

void camera::update()
{
	float x = -m_position.get_x();
	float y = -m_position.get_y();
	float scale_x = m_scale * (m_w / (float)m_h);
	float scale_y = m_scale;
	m_view = math::ortho(x-scale_x, m_w + x + scale_x, m_h + y + scale_y, y-scale_y, -1, 1);
}
