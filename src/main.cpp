#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vse/window.hpp>
#include <vse/input.hpp>

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
	if (!glfwInit())
	{
		printf("Cannot ininialize glfw context\n");
		exit(EXIT_FAILURE);
	}

	std::unique_ptr<Window> w = nullptr;
	try {
		w = std::make_unique<Window>(640, 480, "bery good");
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	w->set_pos(400, 100);
	w->set_size(500, 200);

	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	Input::get().on_key(on_key);
	Input::get().on_mouse(on_mouse);
	Input::get().on_scroll(on_scroll);

	Input::get().on_key([&w](event_key e) {
		if (e.key == GLFW_KEY_ESCAPE)
			w->close();
	});

	glfwSwapInterval(1);
	while (w->is_open())
	{
		w->swap_buffers();
		glfwPollEvents();
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

