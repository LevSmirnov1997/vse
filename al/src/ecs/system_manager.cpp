#include "system_manager.hpp"

void system_manager::add(std::unique_ptr<System> ptr)
{
	m_sys.push_back(std::move(ptr));
}

void system_manager::update(ecs &m) const
{
	for (auto &s : m_sys)
		s->update(m);
}
