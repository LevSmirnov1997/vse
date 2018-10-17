#include "input.hpp"

Input& Input::get()
{
	static Input inst;
	return inst;
}

cb_id Input::on_key(cb_key cb)
{
	m_cb_keys.emplace(m_next_id, cb);
	return m_next_id++;
}

cb_id Input::on_mouse(cb_mouse cb)
{
	m_cb_mouse.emplace(m_next_id, cb);
	return m_next_id++;
}

cb_id Input::on_scroll(cb_scroll cb)
{
	m_cb_scroll.emplace(m_next_id, cb);
	return m_next_id++;
}

void Input::remove_cb(cb_id id)
{
	if (m_cb_keys.erase(id))
		return;
	if (m_cb_mouse.erase(id))
		return;
	if (m_cb_scroll.erase(id))
		return;
}

void Input::callback_key(int key, int /*scancode*/, int action, int mods)
{
	event_key e{ key, action, mods };
	for (const auto &elem : m_cb_keys)
	{
		elem.second(e);
	}
}

void Input::callback_mouse_key(int key, int action, int mods)
{
	this->callback_key(key, 0, action, mods);
}

void Input::callback_mouse_pos(double x, double y)
{
	event_mouse e{ x, y };
	for (const auto &elem : m_cb_mouse)
	{
		elem.second(e);
	}
}

void Input::callback_scroll(double /*xoffset*/, double yofsset)
{
	event_scroll e{ yofsset };
	for (const auto &elem : m_cb_scroll)
	{
		elem.second(e);
	}
}

cb_id Input::on_resize(cb_resize cb)
{
	m_cb_resize.emplace(m_next_id, cb);
	return m_next_id++;
}

void Input::callback_resize(int w, int h)
{
	event_resize e{ w, h };
	for (const auto &elem : m_cb_resize)
	{
		elem.second(e);
	}
}
