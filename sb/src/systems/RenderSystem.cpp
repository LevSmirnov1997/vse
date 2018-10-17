#include "RenderSystem.hpp"
#include <al/ecs.hpp>
#include <al/gl.hpp>

RenderSystem::RenderSystem(const program &p)
	: m_p(p)
{
}

void RenderSystem::update(ecs &e)
{
	m_p.use();
	for (const auto& en : e.with<model>())
	{
		const auto &m = en.get<model>().ptr;
		m->bind();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, m->size(), GL_UNSIGNED_INT, 0);
	}
}
