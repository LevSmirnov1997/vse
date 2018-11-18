#pragma once
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>

/* Keyboard or mouse button */
struct event_key
{
	int key;
	int action;
	int mods;
};

/* Mouse position */
struct event_mouse
{
	double x;
	double y;
};

/* Mouse scroll offset */
struct event_scroll
{
	double offset;
};

/* Window width and heigth */
struct event_resize
{
	int w;
	int h;
};

using cb_id = unsigned long;
using cb_key = std::function<void(event_key)>;
using cb_mouse = std::function<void(event_mouse)>;
using cb_scroll = std::function<void(event_scroll)>;
using cb_resize = std::function<void(event_resize)>;

class Input
{
public:
	Input(const Input&) = delete;

	Input & operator=(const Input&) = delete;

	static Input &get();

	cb_id on_key(cb_key cb);

	cb_id on_mouse(cb_mouse cb);

	cb_id on_scroll(cb_scroll cb);

	cb_id on_resize(cb_resize cb);

	void remove_cb(cb_id id);

	event_mouse get_mouse_pos() const;

private:
	Input();

	friend class Window;

	void callback_key(int key, int scancode, int action, int mods);

	void callback_mouse_pos(double x, double y);

	void callback_mouse_key(int key, int action, int mods);

	void callback_scroll(double xoffset, double yofsset);

	void callback_resize(int w, int h);

	std::unordered_map<cb_id, cb_key>    m_cb_keys;
	std::unordered_map<cb_id, cb_mouse>  m_cb_mouse;
	std::unordered_map<cb_id, cb_scroll> m_cb_scroll;
	std::unordered_map<cb_id, cb_resize> m_cb_resize;
	cb_id m_next_id = 0;
	event_mouse m_last_mouse = { 0, 0 };
};
