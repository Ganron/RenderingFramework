#include"CoreSystems/Math/Vector4.h"
#include"CoreSystems/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Texture.h"


/******************************
**** FOR TESTING PURPOSES *****
******************************/

#include<stdio.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

GLuint compileShaders();

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
	GLuint renderingProgram;

	renderingProgram = compileShaders();

	/*********************/
	Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::CLAMP_BORDER, Graphics::TexWrap::CLAMP_BORDER);
	Graphics::Texture tex;
	tex.Load("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\COMMUNISM.png", config);
	tex.Bind(0);	

	glCreateVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	while(!window.IsClosed())
	{
		Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		/*FOR TESTING PURPOSES*/
		glUseProgram(renderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		/*********************/
		window.Update();
	}

	/*FOR TESTING PURPOSES*/
	glDeleteProgram(renderingProgram);
	glDeleteVertexArrays(1, &vertexArray);
	/**********************/

	tex.Unload();

	return 0;
}

/******************************
**** FOR TESTING PURPOSES *****
******************************/

GLuint compileShaders()
{
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	std::string strVertexSource = "#version 450 core\n"
		"void main(void)\n"
	"{\n"
		"vec4 positions[] = { vec4(-1.0, -1.0, 0.0, 1.0),\n"
		"					vec4(1.0, -1.0, 0.0, 1.0),\n"
		"					vec4(1.0, 1.0, 0.0, 1.0),\n"
		"\n"
		"					vec4(-1.0, -1.0, 0.0, 1.0),\n"
		"					vec4(1.0, 1.0, 0.0, 1.0),\n"
		"					vec4(-1.0, 1.0, 0.0, 1.0) };\n"
		"gl_Position = positions[gl_VertexID];\n"
	"}\n";
	static const char* vertexSource = strVertexSource.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	std::string strFragmentSource = "#version 450 core\n"
		"uniform sampler2D tex;\n"
		"out vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"	color = texture(tex, gl_FragCoord.xy / textureSize(tex,0));\n"
		"	//color=texelFetch(tex, ivec2(gl_FragCoord.xy), 0);\n"
		"	if(color.w==0.0) color = vec4(1.0, 0.0, .0, 1.0);\n"
		"}\n";
	static const char* fragmentSource = strFragmentSource.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

/******************************/