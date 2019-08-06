#pragma once
#include <vector>
#include <unordered_map>
#include <exception>
#include <algorithm>

using eid = size_t;

namespace detail
{
	class pool
	{
	public:
		template <typename T>
		bool has(eid id)
		{
			return id < m_ids.size() && m_ids[id] >= 0;
		}

		template <typename T, typename ...Args>
		bool add(eid id, Args&& ...args)
		{
			if (this->has<T>(id))
				return false;
			m_ids.resize(id + 1, -1);
			m_data.resize(offset + sizeof(T));

			T *ptr = reinterpret_cast<T*>(&m_data[offset]);
			new (ptr) T{ std::forward<Args&&>(args)... };

			m_ids[id] = offset;
			offset += sizeof(T);
			return true;
		}

		template <typename T>
		T& get(eid id)
		{
			if (!this->has<T>(id))
				throw std::runtime_error("Entity has no component of this type");
			return *reinterpret_cast<T*>(&m_data[m_ids[id]]);
		}

		template <typename T>
		bool remove(eid id)
		{
			if (!this->has<T>(id))
				return false;
			m_ids[id] = -1;
			return true;
		}

	private:
		std::vector<int> m_ids;
		std::vector<unsigned char> m_data;
		size_t offset = 0;
	};

	template <typename>
	void type_id() { }

	using type_id_t = void(*)();
}

class component_manager
{
public:
	template <typename T>
	bool has(eid id)
	{
		return m_cmp[detail::type_id<T>].template has<T>(id);
	}

    template <typename ...T>
    bool has_all(eid id)
    {
        std::vector<bool> res = { has<T>(id)... };
        return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
    }

	template <typename T, typename ...Args>
	bool add(eid id, Args&& ...args)
	{
		return m_cmp[detail::type_id<T>].template add<T, Args...>(id, std::forward<Args&&>(args)...);
	}

	template <typename T>
	T& get(eid id)
	{
		return m_cmp[detail::type_id<T>].template get<T>(id);
	}

	template <typename T>
	bool remove(eid id)
	{
		return m_cmp[detail::type_id<T>].template remove<T>(id);
	}

private:
	std::unordered_map<detail::type_id_t, detail::pool> m_cmp;
};
