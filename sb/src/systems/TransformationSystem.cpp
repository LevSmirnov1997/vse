#include "TransformationSystem.hpp"
#include <al/math/mat_utils.hpp>
#include <al/gl.hpp>

void TransformationSystem::update(ecs &ens)
{
	for (const auto &e : ens.with<transform>())
	{
		while (!m_keyque.empty())
		{
			mat4 &t = e.get<transform>().transf;
			if (m_keyque.front() == GLFW_KEY_Q)
				t = math::rotate(t, 6);
			if (m_keyque.front() == GLFW_KEY_E)
				t = math::rotate(t, -6);

			if (m_keyque.front() == GLFW_KEY_UP)
				t = math::translate(t, vec2(0, 0.1f));
			if (m_keyque.front() == GLFW_KEY_DOWN)
				t = math::translate(t, vec2(0, -0.1f));
			if (m_keyque.front() == GLFW_KEY_LEFT)
				t = math::translate(t, vec2(-0.1f, 0));
			if (m_keyque.front() == GLFW_KEY_RIGHT)
				t = math::translate(t, vec2(0.1f, 0));

			if (m_keyque.front() == GLFW_KEY_S)
				t = math::scale(t, vec2(1, 0.9f));
			if (m_keyque.front() == GLFW_KEY_W)
				t = math::scale(t, vec2(1, 1.1f));
			if (m_keyque.front() == GLFW_KEY_A)
				t = math::scale(t, vec2(0.9, 1));
			if (m_keyque.front() == GLFW_KEY_D)
				t = math::scale(t, vec2(1.1, 1));

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
