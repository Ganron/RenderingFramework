#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace Graphics
{
	class Window
	{
	private:
		GLFWwindow* window;
		const char* title;
		int width;
		int height;
		bool bFullscreen;

	public:
		Window(int inWidth, int inHeight, const char* inTitle, bool inFullscreen = 0);

		void SetSize(int inWidth, int inHeght);
		void SetTitle(const char* inTitle);
		void SetFullscreen(bool inFullscreen);

		void GetSize(int& outWidth, int& outHeight) const;
		const char* GetTitle() const;

		bool IsFullscreen() const;
		bool IsClosed() const;

		void Update();

		~Window();
	};
}
//TODO add fullscreen functionality