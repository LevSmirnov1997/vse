#include "window.hpp"
#include "input.hpp"
#include <iostream>

Window::Window(int width, int height, const char *title, bool fullscreen)
{
	glfwSetErrorCallback(callback_error);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_w = fullscreen ?
		glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL) :
		glfwCreateWindow(width, height, title, NULL, NULL);

	if (m_w == NULL) {
		throw std::exception("Failed to create a window");
	}

	// some dark magic from https://stackoverflow.com/questions/7676971/
	#define generic_callback(function_name)\
		[](GLFWwindow *window, auto... args) {\
			auto ptr = static_cast<Input*>(glfwGetWindowUserPointer(window));\
			ptr->function_name(args...);\
		}

	// set callbacks
	glfwSetKeyCallback(m_w, generic_callback(Input::get().callback_key));
	glfwSetMouseButtonCallback(m_w, generic_callback(Input::get().callback_mouse_key));
	glfwSetCursorPosCallback(m_w, generic_callback(Input::get().callback_mouse_pos));
	glfwSetScrollCallback(m_w, generic_callback(Input::get().callback_scroll));
	glfwMakeContextCurrent(m_w);
}

Window::~Window()
{
	glfwDestroyWindow(m_w);
}

void Window::set_pos(int x, int y) const
{
	glfwSetWindowPos(m_w, x, y);
}

void Window::set_size(int w, int h) const
{
	glfwSetWindowSize(m_w, w, h);
}

void Window::callback_error(int error, const char *descr)
{
	std::cerr << "Error " << error << " : " << descr << std::endl;
}
