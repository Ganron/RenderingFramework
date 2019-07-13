#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"CoreSystems/Math//Vector4.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}
	
	glViewport(0, 0, 800, 600);

	while(!glfwWindowShouldClose(window))
	{
		Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}