#include"CoreSystems/Math/Vector4.h"
#include"CoreSystems/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Texture.h"
#include"Graphics/ShaderProgram.h"


/******************************
**** FOR TESTING PURPOSES *****
******************************/

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void generateTexture(unsigned char* data, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data[(y * width + x) * 4 + 0] = 0;
			data[(y * width + x) * 4 + 1] = 255;
			data[(y * width + x) * 4 + 2] = 255;
			data[(y * width + x) * 4 + 3] = 255;
		}
	}
}
/******************************/

int main()
{
	Graphics::Window window(800, 600, "Test", false);

	/*FOR TESTING PURPOSES*/
	GLuint vertexArray;
	/*********************/

	Graphics::ShaderProgram program;
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\VertexShader.vert", Graphics::ShaderType::VERTEX);
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\FragmentShader.frag", Graphics::ShaderType::FRAGMENT);
	program.LinkProgram();

	Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::CLAMP_BORDER, Graphics::TexWrap::CLAMP_BORDER);
	Graphics::Texture tex;
	tex.Load("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\COMMUNISM.png", config);
	tex.Bind(0);	

	glCreateVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	program.UseProgram();

	int uniform[8] = { 10,-43,1,1,0,69,0,0 };
	program.SetUniform(0, 8, uniform);

	while(!window.IsClosed())
	{
		Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		/*FOR TESTING PURPOSES*/
		glDrawArrays(GL_TRIANGLES, 0, 6);
		/*********************/
		window.Update();
	}

	/*FOR TESTING PURPOSES*/
	glDeleteVertexArrays(1, &vertexArray);
	/**********************/

	tex.Unload();
	program.Delete();

	return 0;
}

//TODO think of a better way to delete objects than an explicit delete function!