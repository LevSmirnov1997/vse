#include "RenderSystem.hpp"
#include <al/ecs.hpp>
#include <al/gl.hpp>
#include <al/math.hpp>
#include <components/transform.hpp>

RenderSystem::RenderSystem(const program &p, int w, int h)
	: m_p(p),
	  m_projection(math::ortho(0, w, h, 0, -1, 1))
{
	Input::get().on_resize([this](event_resize e){
		this->m_projection = math::ortho(0, e.w, e.h, 0, -1, 1);
	});
}

void RenderSystem::update(ecs &e)
{
	m_p.use();
	for (const entity& en : e.with<model>())
	{
		const auto &m = en.get<model>();
		const mat4 &t = en.has<transform>() ? en.get<transform>().transf : mat4();
		m_p.set_mat4("MVP", math::mult(m_projection, t).get_values());

		m.ptr->bind();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, m.ptr->size(), GL_UNSIGNED_INT, 0);
	}
}
