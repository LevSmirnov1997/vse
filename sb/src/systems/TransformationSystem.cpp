#include "TransformationSystem.hpp"

void TransformationSystem::update(ecs &ens)
{
	for (const auto &e : ens.with<Transform>())
	{
		while (!m_keyque.empty())
		{
			if (m_keyque.front() == GLFW_KEY_UP)
				e.get<Transform>().scale(2, 3);
			else if (m_keyque.front() == GLFW_KEY_LEFT)
				e.get<Transform>().move(1, -3);
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