#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
	std::fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	if (!glfwInit())
	{
		printf("Cannot ininialize glfw context\n");
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(error_callback);

	GLFWwindow *w = glfwCreateWindow(640, 480, "VSE", NULL, NULL);
	if (!w)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// set callbacks
	glfwSetKeyCallback(w, key_callback);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSwapInterval(1);

	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	while (!glfwWindowShouldClose(w))
	{
		glfwSwapBuffers(w);
		glfwPollEvents();
	}


	glfwDestroyWindow(w);
	glfwTerminate();
    exit(EXIT_SUCCESS);
}

