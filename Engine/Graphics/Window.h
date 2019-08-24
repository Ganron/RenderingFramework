#pragma once
#include"Camera.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

namespace Graphics
{
	class Window
	{
	private:
		std::string title;
		GLFWwindow* window;
		static Camera* camera;

		static int width; //static so it can be accessed by glfw size callback.
		static int height; //static so it can be accessed by glfw size callback.

		static float cursorLastX; //static so it can be accessed by glfw mouse callback.
		static float cursorLastY; //static so it can be accessed by glfw mouse callback.

		static bool bFirstMouseMov; //static so it can be accessed by glfw size callback.
		static bool bFullscreen; //static so it can be accessed by glfw size callback.

		static void FramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight);
		static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	public:
		Window(int inWidth, int inHeight, const std::string& inTitle, bool inFullscreen = 0);

		void SetSize(int inWidth, int inHeght);
		void SetTitle(const std::string& inTitle);
		void ToggleFullscreen();
		void ProcessInput(float deltaTime);

		void GetSize(int& outWidth, int& outHeight) const;
		float GetAspectRatio() const;
		std::string GetTitle() const;
		const Camera* GetCamera() const;

		bool IsFullscreen() const;
		bool IsClosed() const;

		//TODO remove deltaTime
		void Update(float deltaTime);

		~Window();
	};
}