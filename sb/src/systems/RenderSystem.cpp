#include "RenderSystem.hpp"
#include "behaviours.hpp"
#include <al/ecs.hpp>
#include <al/gl.hpp>
#include <al/math.hpp>
#include <components/transform.hpp>

RenderSystem::RenderSystem(const program &p, int w, int h)
	: m_p(p),
	  m_cam(w, h),
	  m_w(w), m_h(h)
{
	Input::get().on_resize([this](event_resize e){
		this->m_cam.resize(e.w, e.h);
		this->m_w = e.w;
		this->m_h = e.h;
	});

	Input::get().on_scroll([this](event_scroll e){
		this->m_cam.scale(-20.f * (float)e.offset);
	});

	Input::get().on_key([this](event_key e){
		if (e.key == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			if (e.action == GLFW_PRESS)
			{
				this->is_moving = true;
				auto pos = Input::get().get_mouse_pos();
				this->m_last_mouse = { (float)pos.x, (float)pos.y };
			}
			else if (e.action == GLFW_RELEASE)
				this->is_moving = false;
		}
	});
}

void RenderSystem::update(ecs &e)
{
	m_p.use();
	for (const entity& en : e.with<model>())
	{
		const auto &m = en.get<model>();
		const mat4 &t = en.has<transform>() ? en.get<transform>().transf : mat4();
		if (is_moving)
		{
			auto cur_pos = Input::get().get_mouse_pos();
			vec2 diff = vec2((float)cur_pos.x, (float)cur_pos.y) - m_last_mouse;
			m_cam.move(diff);
			m_last_mouse = { (float)cur_pos.x, (float)cur_pos.y };
		}
		auto p = Input::get().get_mouse_pos();

		seek(en.get<transform>(), m_cam.world_to_view({ (float)p.x, (float)p.y }));

		const float *v = m_cam.get().get_values();
		m_p.set_mat4("MVP", math::mult(m_cam.get(), t).get_values());

		m.ptr->bind();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, m.ptr->size(), GL_UNSIGNED_INT, 0);
	}
}
