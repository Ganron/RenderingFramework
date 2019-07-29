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
		int width;
		int height;
		bool bFullscreen;

	public:
		Window(int inWidth, int inHeight, const std::string& inTitle, bool inFullscreen = 0);

		void SetSize(int inWidth, int inHeght);
		void SetTitle(const std::string& inTitle);
		void ToggleFullscreen();
		void ProcessInput();

		void GetSize(int& outWidth, int& outHeight) const;
		std::string GetTitle() const;

		bool IsFullscreen() const;
		bool IsClosed() const;

		void Update();

		~Window();
	};
}
//TODO add fullscreen functionality