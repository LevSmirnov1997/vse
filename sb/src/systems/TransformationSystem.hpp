#pragma once

#include <queue>
#include <al/gl.hpp>
#include <al/ecs.hpp>
#include "components/transform.hpp"



class TransformationSystem : public System
{
public:
	void update(ecs &ens) override;

	TransformationSystem();

private:

	std::queue<int> m_keyque;
};