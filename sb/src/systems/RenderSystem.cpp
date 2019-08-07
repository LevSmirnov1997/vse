#include "RenderSystem.hpp"
#include <al/ecs.hpp>
#include <al/gl.hpp>
#include <al/math.hpp>
#include <components/CTransform.hpp>

RenderSystem::RenderSystem(ecs &e, const program &p, int w, int h)
	: m_p(p),
	  m_cam(e.create())
{
	m_cam.add<camera>(w, h);

	Input::get().on_resize([this](event_resize e){
		this->m_cam.get<camera>().resize(e.w, e.h);
	});

	Input::get().on_scroll([this](event_scroll e){
		this->m_cam.get<camera>().scale(-20.f * (float)e.offset);
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
	camera &cam = m_cam.get<camera>();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (const entity& en : e.with<CModel>())
	{
		const auto &m = en.get<CModel>();
		const mat4 &t = en.has<CTransform>() ? en.get<CTransform>().transf : mat4();
		if (is_moving)
		{
			auto cur_pos = Input::get().get_mouse_pos();
			vec2 diff = vec2((float)cur_pos.x, (float)cur_pos.y) - m_last_mouse;
			cam.move(diff);
			m_last_mouse = { (float)cur_pos.x, (float)cur_pos.y };
		}

		m_p.set_mat4("MVP", math::mult(cam.get(), t).get_values());
		m.ptr->bind();
		glDrawElements(GL_TRIANGLES, m.ptr->size(), GL_UNSIGNED_INT, 0);
	}
}
