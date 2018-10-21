#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

template <typename T>
void type_id() {};

template <typename T>
using cb_t = std::function<void(const T&)>;

using type_id_t = void(*)();

class event_manager
{
 public:
	event_manager() = default;

	~event_manager() = default;

	template <typename T>
	void subscribe(cb_t<T> func) 
	{
			m_cbs[type_id<T>].push_back([&, func](const void* val) {
				func(*reinterpret_cast<const T*>(val));
			});
		
	}

	template <typename T>
	void notify(const T val) 
	{
		auto it = m_cbs.find(type_id<T>);
		if (it != m_cbs.end())
		{
			for (const auto &f : m_cbs[type_id<T>])
				f(reinterpret_cast<const void*>(&val));
		}
	}

	void unsubscribe(type_id_t id)
	{
		if (m_cbs.find(id) != m_cbs.end())
		{
			m_cbs.erase(id);
		}
	}


 private:
	 std::unordered_map<type_id_t, std::vector<std::function<void(const void*)>>> m_cbs;
};