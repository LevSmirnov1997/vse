#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const char *title, bool fullscreen = false);

	~Window();

	void set_pos(int x, int y) const;

	void set_size(int w, int h) const;

	bool is_open() const { return !glfwWindowShouldClose(m_w); }

	void close() const { return glfwSetWindowShouldClose(m_w, true); }

	void swap_buffers() const { glfwSwapBuffers(m_w); }

	int get_w() const { return m_width; }

	int get_h() const { return m_height; }

private:
	GLFWwindow * m_w;
	int m_width;
	int m_height;

	static void callback_error(int error, const char *descr);

	void callback_framebuffer_size(int width, int height);
};
