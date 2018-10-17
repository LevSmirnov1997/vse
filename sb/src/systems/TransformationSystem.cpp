#include "TransformationSystem.hpp"
#include <al/math/mat_utils.hpp>

void TransformationSystem::update(ecs &ens)
{
	for (const auto &e : ens.with<transform>())
	{
		while (!m_keyque.empty())
		{
			if (m_keyque.front() == GLFW_KEY_UP)
				math::translate(e.get<transform>().m_pos, vec2(0, 1.0f));
			else if (m_keyque.front() == GLFW_KEY_DOWN)
				math::translate(e.get<transform>().m_pos, vec2(0, -1.0f));
			else if(m_keyque.front() == GLFW_KEY_LEFT)
				math::translate(e.get<transform>().m_pos, vec2(-1.0f, 0));
			else if (m_keyque.front() == GLFW_KEY_RIGHT)
				math::translate(e.get<transform>().m_pos, vec2(1.0f, 0));
			else if (m_keyque.front() == GLFW_KEY_RIGHT)
				math::translate(e.get<transform>().m_pos, vec2(1.0f, 0));
			m_keyque.pop();
		}
	}
}

TransformationSystem::TransformationSystem()
{
	Input::get().on_key([this](event_key key) {
		m_keyque.push(key.key);
	});
}