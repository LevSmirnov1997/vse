#include "TransformationSystem.hpp"
#include <cmath>
#include <al/math/mat_utils.hpp>
#include <al/gl.hpp>

static void move(transform &t, float step)
{
	float rad = math::radians(t.angle);
	float x = (step * sin(rad));
	float y = -fabs(step * cos(rad));
	if (cos(rad) < 0)
		y = -y;
	if (step < 0)
		y = -y;
	t.transf = math::translate(t.transf, vec2(x, y));
}

static void rotate(transform &t, float degr)
{
	t.angle += degr;
	t.transf = math::rotate(t.transf, degr);
}

void TransformationSystem::update(ecs &ens)
{
	for (const auto &e : ens.with<transform>())
	{
		while (!m_keyque.empty())
		{
			mat4 &t = e.get<transform>().transf;
			if (m_keyque.front() == GLFW_KEY_E)
				rotate(e.get<transform>(), 6);
			else if (m_keyque.front() == GLFW_KEY_Q)
				rotate(e.get<transform>(), -6);

			else if (m_keyque.front() == GLFW_KEY_DOWN)
				t = math::translate(t, vec2(0, 50));
			else if (m_keyque.front() == GLFW_KEY_UP)
				t = math::translate(t, vec2(0, -50));
			else if (m_keyque.front() == GLFW_KEY_LEFT)
				t = math::translate(t, vec2(-50, 0));
			else if (m_keyque.front() == GLFW_KEY_RIGHT)
				t = math::translate(t, vec2(50, 0));

			else if (m_keyque.front() == GLFW_KEY_S)
				t = math::scale(t, vec2(1, 0.9f));
			else if (m_keyque.front() == GLFW_KEY_W)
				t = math::scale(t, vec2(1, 1.1f));
			else if (m_keyque.front() == GLFW_KEY_A)
				t = math::scale(t, vec2(0.9, 1));
			else if (m_keyque.front() == GLFW_KEY_D)
				t = math::scale(t, vec2(1.1, 1));

			else if (m_keyque.front() == GLFW_KEY_KP_8)
				move(e.get<transform>(), 10);
			else if (m_keyque.front() == GLFW_KEY_KP_2)
				move(e.get<transform>(), -10);

			m_keyque.pop();
		}
	}
}

TransformationSystem::TransformationSystem()
{
	Input::get().on_key([this](event_key key) {
		if (key.action == GLFW_PRESS || key.action == GLFW_REPEAT)
			m_keyque.push(key.key);
	});
}
