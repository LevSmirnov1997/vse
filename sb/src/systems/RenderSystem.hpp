#pragma once
#include <al/ecs/system_manager.hpp>
#include <al/gl/program.hpp>
#include <al/math/mat4.hpp>
#include <al/gl/camera.hpp>
#include <components/model.hpp>

class RenderSystem : public System
{
public:
	RenderSystem() = delete;

	RenderSystem(const program &p, int w, int h);

	void update(ecs &e) override;

private:
	const program &m_p;
	camera m_cam;
	bool is_moving = false;
	vec2 m_last_mouse;
	float m_w, m_h;
};
