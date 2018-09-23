#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vse/window.hpp>
#include <vse/input.hpp>
#include <vse/program.hpp>

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
		Window w{ 640, 480, "bery good" };
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		w.set_pos(400, 100);

		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

		Input::get().on_key(on_key);
		Input::get().on_mouse(on_mouse);
		Input::get().on_scroll(on_scroll);
		Input::get().on_key([&w](event_key e) {
			if (e.key == GLFW_KEY_ESCAPE)
				w.close();
		});

		program p = program::create_progarm( {
				{ GL_VERTEX_SHADER,   "../shaders/basic.sv" },
				{ GL_FRAGMENT_SHADER, "../shaders/basic.sf" }
			}
		);
		std::cerr << p.info_log() << std::endl;
		if (!p.valid()) {
			std::cerr << p.info_log() << std::endl;
			throw;
		}
		p.use();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		};

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		glfwSwapInterval(1);
		while (w.is_open())
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0, 3);

			w.swap_buffers();
			glfwPollEvents();
		}
	}
	catch (const std::exception &e)	{
		std::cerr << e.what() << std::endl;
	}
	glfwTerminate();
	return 0;
}

