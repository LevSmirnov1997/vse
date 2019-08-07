#include <iostream>
#include <cstring>
#include <al/gl.hpp>
#include <al/ecs.hpp>
#include <al/math.hpp>
#include <systems/TransformationSystem.hpp>
#include <systems/RenderSystem.hpp>
#include "behaviours.hpp"
#include <chrono>
#include <thread>

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

class CursorBehaviorSystem : public System
{
	enum mode
	{
		mode_seek = 1,
		mode_flee,
		mode_wander,
	};

	mode m_mode = mode_seek;

public:
	CursorBehaviorSystem()
	{
		Input::get().on_key(
			[this](event_key e) {
				if (e.action != GLFW_PRESS)
					return;
				if (e.key == GLFW_KEY_1)
					this->m_mode = mode_seek;
				else if (e.key == GLFW_KEY_2)
					this->m_mode = mode_flee;
				else if (e.key == GLFW_KEY_3)
					this->m_mode = mode_wander;
		    }
		);
	}

	void update(ecs &e) override
	{
		camera *cam = nullptr;
		for (auto en : e.with<camera>())
		{
			cam = &en.get<camera>();
			break;
		}
		if (nullptr == cam)
			return;

		auto p = Input::get().get_mouse_pos();
		vec2 cursor_pos { cam->world_to_view({ (float)p.x, (float)p.y }) };
		for (auto en : e.with<CTransform>())
		{
			switch (m_mode)
			{
			case CursorBehaviorSystem::mode_seek:
				seek(en.get<CTransform>(), cursor_pos);
				break;
			case CursorBehaviorSystem::mode_flee:
				flee(en.get<CTransform>(), cursor_pos);
				break;
			case CursorBehaviorSystem::mode_wander:
				wander(en.get<CTransform>());
				break;
			default:
				break;
			}
		}
	}
};

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
		e.add_system(std::make_unique<RenderSystem>(e, p, w.get_w(), w.get_h()));
		e.add_system(std::make_unique<TransformationSystem>());
		e.add_system(std::make_unique<CursorBehaviorSystem>());

		{
			auto rect = e.create();
			rect.add<CModel>(std::make_unique<Triangle>());
			rect.add<CTransform>(mat4(), 0.f, vec2(), 2.f, 100.f);
			auto & t = rect.get<CTransform>().transf;
			t = math::translate(t, vec2(200, 100));
		}

		glfwSwapInterval(1);
		while (w.is_open())
		{
			e.update();

			w.swap_buffers();
			glfwPollEvents();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
	(void)argc;
}

