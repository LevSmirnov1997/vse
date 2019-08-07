#pragma once
#include <al/gl/program.hpp>
#include <al/ecs.hpp>
#include <al/math/mat4.hpp>
#include <al/math/vec2.hpp>
#include <components/CModel.hpp>

class RenderSystem : public System
{
public:
	RenderSystem() = delete;

	RenderSystem(ecs &e, const program &p, int w, int h);

	void update(ecs &e) override;

private:
	const program &m_p;
	bool is_moving = false;
	vec2 m_last_mouse;
	entity m_cam;
};
