#include"Window.h"
namespace Graphics
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	Window::Window(int inWidth, int inHeight, const char * inTitle, bool inFullscreen) : width(inWidth), height(inHeight), title(inTitle), bFullscreen(inFullscreen)
	{
		//TODO decide whether the initialization of glfw and glad should be done here

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

		window = glfwCreateWindow(width, height, title, NULL, NULL);
		//TODO ASSERT(window)?

		glfwMakeContextCurrent(window);

		//TODO check whether glad is properly initialized
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

		glViewport(0, 0, width, height);
	}

	void Window::SetSize(int inWidth, int inHeight)
	{
		width = inWidth;
		height = inHeight;
	}

	void Window::SetTitle(const char * inTitle)
	{
		title = inTitle;
	}

	void Window::SetFullscreen(bool inFullscreen)
	{
		bFullscreen = inFullscreen;
	}

	void Window::GetSize(int & outWidth, int & outHeight) const
	{
		outWidth = width;
		outHeight = height;
	}

	const char * Window::GetTitle() const
	{
		return title;
	}

	bool Window::IsFullscreen() const
	{
		return bFullscreen;
	}

	bool Window::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::Update()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

}
