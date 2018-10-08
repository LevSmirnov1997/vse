#include <iostream>
#include <vector>
#include <vse/window.hpp>
#include <vse/input.hpp>
#include <vse/program.hpp>
#include <vse/shapes.hpp>
#include <vse/ecs.hpp>

struct Model
{
	std::unique_ptr<shape> data;
};

class Renderer : public System
{
public:
	void update(ecs &ens) override
	{
		for (const auto &e : ens.with<Model>())
		{
			const auto &r = e.get<Model>().data;
			r->bind();
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, r->size(), GL_UNSIGNED_INT, 0);
		}
	}
};


int main()
{
	try {
		Window w{ 800, 800, "bery good" };
		w.set_pos(400, 100);

		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

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

		ecs e;
		e.add_system(std::make_unique<Renderer>());

		auto rect = e.create();
		rect.add<Model>(std::make_unique<Rect>());

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
}

