#pragma once
#include <vse/component_manager.hpp>
#include <vse/system_manager.hpp>
#include <algorithm>
#include <unordered_set>

class entity_manager;

class entity
{
public:
	template <typename T>
	bool has() const
	{
		return m_man.has<T>(m_id);
	}

	template <typename T, typename ...Args>
	bool add(Args&& ...args) const
	{
		return m_man.template add<T, Args...>(m_id, std::forward<Args&&>(args)...);
	}

	template <typename T>
	T& get() const
	{
		return m_man.get<T>(m_id);
	}

	template <typename T>
	bool remove() const
	{
		return m_man.remove<T>(m_id);
	}

private:
	friend class ecs;

	entity(eid id, component_manager &m)
		: m_id(id), m_man(m)
	{
	}

	eid m_id;
	component_manager &m_man;
};

class ecs
{
public:
	entity create();

	void remove(entity e);

	std::vector<entity> get() const;

	void add_system(std::unique_ptr<System> ptr);

	void update();

	template <typename T>
	std::vector<entity> with() const
	{
		std::vector<entity> res;
		for (const auto &e : m_ens)
		{
			if (e.has<T>())
				res.push_back(e);
		}
		return res;
	}

private:
	system_manager m_sys;
	component_manager m_com;
	std::vector<entity> m_ens;
	eid m_next_id = 1;
};
