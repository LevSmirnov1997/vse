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

private:
	GLFWwindow * m_w;

	static void callback_error(int error, const char *descr);

	static void callback_framebuffer_size(GLFWwindow *w, int width, int height);
};
