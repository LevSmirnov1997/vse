#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

namespace details
{
	template <typename T>
	void type_id() {};

	using type_id_t = void(*)();
}

template <typename T>
using cb_t = std::function<void(const T&)>;

class event_manager
{
 public:
	event_manager() = default;

	~event_manager() = default;

	template <typename T>
	void subscribe(cb_t<T> func) 
	{
			m_cbs[details::type_id<T>].push_back([&, func](const void* val) {
				func(*reinterpret_cast<const T*>(val));
			});
	}

	template <typename T>
	void notify(const T &val) 
	{	
		for (const auto &f : m_cbs[details::type_id<T>])
			f(reinterpret_cast<const void*>(&val));
	}

 private:
	 std::unordered_map<details::type_id_t, std::vector<std::function<void(const void*)>>> m_cbs;
};