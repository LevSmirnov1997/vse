#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vse/window.hpp>
#include <vse/input.hpp>
#include <vse/program.hpp>
#include <vse/shapes.hpp>

static void on_key(event_key e)
{
	std::cout << "Key: " << e.key << " " << e.mods;
	if (e.action == GLFW_REPEAT) {
		std::cout << " repeated";
	}
	else if (e.action == GLFW_PRESS) {
		std::cout << " pressed";
	}
	else {
		std::cout << " released";
	}
	std::cout << std::endl;
}

static void on_mouse(event_mouse e)
{
	std::cout << "Mouse pos changed to: " << e.x << " " << e.y << std::endl;
}

static void on_scroll(event_scroll e)
{
	std::cout << "Mouse scroll offset: " << e.offset << std::endl;
}


int main()
{
	try {
		if (!glfwInit())
		{
			printf("Cannot ininialize glfw context\n");
			exit(EXIT_FAILURE);
		}
		Window w{ 800, 800, "bery good" };
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD\n";
			return -1;
		}
		w.set_pos(400, 100);

		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

		Input::get().on_key(on_key);
		Input::get().on_mouse(on_mouse);
		Input::get().on_scroll(on_scroll);
		Input::get().on_key([&w](event_key e) {
			if (e.key == GLFW_KEY_ESCAPE)
				w.close();
		});

		program p = program::create_progarm({
				{ GL_VERTEX_SHADER,   "../shaders/basic.sv" },
				{ GL_FRAGMENT_SHADER, "../shaders/basic.sf" }
			}
		);
		if (!p.valid()) {
			std::cerr << p.info_log() << std::endl;
			throw;
		}
		p.use();

		Rect r;

		glfwSwapInterval(1);
		while (w.is_open())
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			r.bind();
			glDrawElements(GL_TRIANGLES, r.size(), GL_UNSIGNED_INT, 0);

			w.swap_buffers();
			glfwPollEvents();
		}
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	glfwTerminate();
	return 0;
}

