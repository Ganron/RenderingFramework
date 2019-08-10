#pragma once

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
		static int width; //static so it can be changed by glfw size callback.
		static int height; //static so it can be changed by glfw size callback.
		static bool bFullscreen;

		static void FramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight);

	public:
		Window(int inWidth, int inHeight, const std::string& inTitle, bool inFullscreen = 0);

		void SetSize(int inWidth, int inHeght);
		void SetTitle(const std::string& inTitle);
		void ToggleFullscreen();
		void ProcessInput();

		void GetSize(int& outWidth, int& outHeight) const;
		float GetAspectRatio() const;
		std::string GetTitle() const;

		bool IsFullscreen() const;
		bool IsClosed() const;

		void Update();

		~Window();
	};
}