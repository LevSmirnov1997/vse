#pragma once
#include "component_manager.hpp"
#include "system_manager.hpp"
#include <algorithm>
#include <unordered_set>

class entity_manager;

class entity
{
public:
    entity() = delete;

    entity(const entity&) = default;

    entity& operator=(const entity&) = default;

    bool operator==(const entity &e)
    {
        return this->m_id == e.m_id;
    }

    template <typename ...T>
    bool has() const
    {
        if (! valid())
        {
            // TODO: add logging
            return false;
        }
		return m_man.template has_all<T...>(m_id);
    }

	template <typename T, typename ...Args>
	bool add(Args&& ...args) const
	{
        if (! valid())
        {
            // TODO: add logging
            return false;
        }
		return m_man.template add<T, Args...>(m_id, std::forward<Args&&>(args)...);
	}

	template <typename T>
	T& get() const
	{
        if (! valid())
        {
            // TODO: add logging
        }
		return m_man.template get<T>(m_id);
	}

	template <typename T>
	bool remove() const
	{
        if (! valid())
        {
            // TODO: add logging
            return false;
        }
		return m_man.template remove<T>(m_id);
	}

    bool valid() const;

private:
	friend class ecs;

	entity(eid id, component_manager &m, ecs &e)
        : m_id(id),
          m_man(m),
          m_ecs(e)
	{
	}

	eid m_id;
	component_manager &m_man;
    ecs &m_ecs;
};

class ecs
{
public:
    ecs();

    ecs(const ecs&) = delete;

    ecs& operator=(const ecs&) = delete;

	entity create();

	void remove(entity e);

    bool is_valid(entity e) const;

	std::vector<entity> get() const;

	void add_system(std::unique_ptr<System> ptr);

	void update();

	template <typename ...T>
	std::vector<entity> with() const
	{
		std::vector<entity> res;
		for (const auto &e : m_ens)
		{
			if (e.has<T...>() && is_valid(e))
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
