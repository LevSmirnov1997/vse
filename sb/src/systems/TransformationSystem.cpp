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
			if (m_keyque.front() == GLFW_KEY_UP)
				t = math::translate(t, vec2(0, 0.1f));
			else if (m_keyque.front() == GLFW_KEY_DOWN)
				t = math::translate(t, vec2(0, -0.1f));
			else if(m_keyque.front() == GLFW_KEY_LEFT)
				t = math::translate(t, vec2(-0.1f, 0));
			else if (m_keyque.front() == GLFW_KEY_RIGHT)
				t = math::translate(t, vec2(0.1f, 0));
			else if (m_keyque.front() == GLFW_KEY_RIGHT)
				t = math::translate(t, vec2(0.1f, 0));
			m_keyque.pop();
		}
	}
}

TransformationSystem::TransformationSystem()
{
	Input::get().on_key([this](event_key key) {
		if (key.action == GLFW_PRESS)
			m_keyque.push(key.key);
	});
}
