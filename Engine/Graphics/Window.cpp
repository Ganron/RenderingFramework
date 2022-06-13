#include"Window.h"
#include"Camera.h"
#include<iostream>

namespace Graphics
{
	Camera* Window::camera = nullptr;

	int Window::width = 0;
	int Window::height = 0;

	float Window::cursorLastX = 0.0f;
	float Window::cursorLastY = 0.0f;

	bool Window::bFullscreen = false;
	bool Window::bFirstMouseMov = true;
	

	void Window::FramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight)
	{
		
		glViewport(0, 0, newWidth, newHeight);
		if (!bFullscreen)
		{
			width = newWidth;
			height = newHeight;
		}
	}

	void Window::MouseCallback(GLFWwindow * window, double xPos, double yPos)
	{
		if (bFirstMouseMov)
		{
			cursorLastX = (float)xPos;
			cursorLastY = (float)yPos;
			bFirstMouseMov = false;
		}
		
		float xDelta = cursorLastX - (float)xPos;
		float yDelta = (float)yPos - cursorLastY;
		
		cursorLastX = (float)xPos;
		cursorLastY = (float)yPos;

		camera->RotateCamera(xDelta, yDelta);
	}

	void Window::ScrollCallback(GLFWwindow * window, double xOffset, double yOffset)
	{
		camera->ZoomCamera((float)yOffset);
	}

	Window::Window(int inWidth, int inHeight, const std::string& inTitle, bool inFullscreen) : title(inTitle)
	{
		width = inWidth;
		height = inHeight;
		bFullscreen = inFullscreen;
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

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

		camera = new Camera;

		//TODO move to a context class (with proper itialization checks)
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetScrollCallback(window, ScrollCallback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	void Window::ProcessInput(float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			ToggleFullscreen();
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::FORWARD, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::BACKWARD, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::LEFT, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::RIGHT, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::UP, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera->MoveCamera(CameraMovementDirection::DOWN, deltaTime);
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

	const Camera * Window::GetCamera() const
	{
		return camera;
	}

	bool Window::IsFullscreen() const
	{
		return bFullscreen;
	}

	bool Window::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::Update(float deltaTime)
	{
		ProcessInput(deltaTime);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Window::~Window()
	{
		delete camera;
		glfwTerminate();
	}

}
