#include <iostream>
#include <vector>
#include <cstring>
#include <al/gl.hpp>
#include <al/ecs.hpp>
#include <al/math.hpp>
#include <systems/TransformationSystem.hpp>
#include <systems/RenderSystem.hpp>

std::string get_program_path(const char *arg)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	static const char slash = '\\';
#else
	static const char slash = '/';
#endif
	const char *end = std::strrchr(arg, slash);
	return { arg, size_t(end - arg) };
}

int main(int argc, char **argv)
{
	const std::string current_path = get_program_path(argv[0]);
	try {
		Window w{ 800, 800, "bery good" };
		w.set_pos(400, 100);

		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

		Input::get().on_key([&w](event_key e) {
			if (e.key == GLFW_KEY_ESCAPE)
				w.close();
		});

		program p = program::create_progarm({
				{ GL_VERTEX_SHADER,   { current_path + "/shaders/basic.sv" } },
				{ GL_FRAGMENT_SHADER, { current_path + "/shaders/basic.sf" } }
			}
		);
		std::cerr << p.info_log() << std::endl;
		if (!p.valid()) {
			std::cerr << p.info_log() << std::endl;
			throw;
		}
		p.use();

		ecs e;
		e.add_system(std::make_unique<RenderSystem>(p));
		e.add_system(std::make_unique<TransformationSystem>());

		auto rect = e.create();
		rect.add<model>(std::make_unique<Rect>());
		rect.add<transform>();

		glfwSwapInterval(1);
		while (w.is_open())
		{
			e.update();

			w.swap_buffers();
			glfwPollEvents();
		}
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
	(void)argc;
}

