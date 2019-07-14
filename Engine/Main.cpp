#include"CoreSystems/Math/Vector4.h"
#include"Graphics/Window.h"

int main()
{
	Graphics::Window window(800,600,"Test");

	while(!window.IsClosed())
	{
		Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		window.Update();
	}

	return 0;
}