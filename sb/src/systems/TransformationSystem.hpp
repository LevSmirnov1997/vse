#pragma once
#include <queue>
#include <al/ecs.hpp>
#include <components/CTransform.hpp>

class TransformationSystem : public System
{
public:
	void update(ecs &ens) override;

	TransformationSystem();

private:
	std::queue<int> m_keyque;
};
