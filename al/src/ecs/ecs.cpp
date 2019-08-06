#include "ecs.hpp"

ecs::ecs()
{
    // add the frist entity with invalid the id
    // so that the condition (entity.m_id < m_ens.size())
    // is correct for valid entities
    entity invalid { 0, m_com, *this };
    m_ens.push_back(invalid);
}

entity ecs::create()
{
	entity e{ m_next_id++, m_com, *this };
	m_ens.push_back(e);
	return e;
}

bool ecs::is_valid(entity e) const
{
    return (e.m_id < m_ens.size()) && (m_ens[e.m_id].m_id != 0);
}

void ecs::remove(entity e)
{
	if (e.m_id < m_ens.size())
		m_ens[e.m_id].m_id = 0;
}

std::vector<entity> ecs::get() const
{
	std::vector<entity> res;
	res.reserve(m_ens.size());
	for (const entity &e : m_ens)
	{
		if (e.m_id)
			res.push_back(e);
	}
	return res;
}

void ecs::add_system(std::unique_ptr<System> ptr)
{
	m_sys.add(std::move(ptr));
}

void ecs::update()
{
	m_sys.update(*this);
}

bool entity::valid() const
{
    return m_ecs.is_valid(*this);
}
