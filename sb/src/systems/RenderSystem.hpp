#pragma once
#include <al/ecs/system_manager.hpp>
#include <al/gl/program.hpp>
#include <al/math/mat4.hpp>
#include <components/model.hpp>

class RenderSystem : public System
{
public:
	RenderSystem() = delete;

	RenderSystem(const program &p, int w, int h);

	void update(ecs &e) override;

private:
	const program &m_p;
	mat4 m_projection;
};
