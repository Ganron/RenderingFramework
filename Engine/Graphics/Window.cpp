#include"Window.h"
#include<iostream>

namespace Graphics
{
	//TODO find a way to change width and height on resize!

	int Window::width = 0;
	int Window::height = 0;
	bool Window::bFullscreen = false;

	void Window::FramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight)
	{
		
		glViewport(0, 0, newWidth, newHeight);
		if (!bFullscreen)
		{
			width = newWidth;
			height = newHeight;
		}
	}

	Window::Window(int inWidth, int inHeight, const std::string& inTitle, bool inFullscreen) : title(inTitle)
	{
		width = inWidth;
		height = inHeight;
		bFullscreen = inFullscreen;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		if (bFullscreen)
		{
			window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, NULL);
		}
		else
		{
			window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
			glfwSetWindowPos(window, (mode->width - this->width) / 2, (mode->height - this->height) / 2);
		}
		
		//TODO ASSERT(window)?

		glfwMakeContextCurrent(window);

		//TODO move to a context class (with proper itialization checks)
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

		//TODO move to rendering class! Should precede drawing!
		glViewport(0, 0, width, height);
	}

	void Window::SetSize(int inWidth, int inHeight)
	{
		width = inWidth;
		height = inHeight;
		glfwSetWindowSize(window, inWidth, inHeight);
	}

	void Window::SetTitle(const std::string& inTitle)
	{
		title = inTitle;
		glfwSetWindowTitle(window, inTitle.c_str());
	}

	void Window::ToggleFullscreen()
	{
		bFullscreen = !bFullscreen;

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		
		if (bFullscreen)
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(window, NULL, (mode->width - this->width) / 2, (mode->height - this->height) / 2, this->width, this->height, 0);
		}
	}

	void Window::ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		//TODO pick another key or make it a const variable
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			ToggleFullscreen();
		}
	}

	void Window::GetSize(int & outWidth, int & outHeight) const
	{
		outWidth = width;
		outHeight = height;
	}

	float Window::GetAspectRatio() const
	{
		if (!bFullscreen)
		{
			return (float)height / (float)width;
		}
		else
		{
			int realHeight;
			int realWidth;
			glfwGetFramebufferSize(window, &realWidth, &realHeight);
			return (float)realHeight / (float)realWidth;
		}
	}

	std::string Window::GetTitle() const
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
		ProcessInput();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

}
