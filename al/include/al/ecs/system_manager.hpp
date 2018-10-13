#pragma once
#include <vector>
#include <memory>

class ecs;

struct System
{
	virtual void update(ecs &m) = 0;
	virtual ~System() { }
};

class system_manager
{
public:

	void add(std::unique_ptr<System> ptr);

	void update(ecs &m) const;

private:
	std::vector<std::unique_ptr<System>> m_sys;
};
