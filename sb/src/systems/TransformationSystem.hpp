#pragma once
class TransformationSystem : public System
{
public:
	void update(ecs &ens) override;

	TransformationSystem();

private:

	std::queue<int> m_keyque;

};