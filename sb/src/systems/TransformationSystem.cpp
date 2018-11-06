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
			if (m_keyque.front() == GLFW_KEY_E)
				e.get<transform>().rotate(6);
			else if (m_keyque.front() == GLFW_KEY_Q)
				e.get<transform>().rotate(-6);

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
                e.get<transform>().move(10);
            else if (m_keyque.front() == GLFW_KEY_KP_2)
                e.get<transform>().move(-10);

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
