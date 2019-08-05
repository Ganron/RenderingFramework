#include"CoreSystems/Math/Vector4.h"
#include"CoreSystems/Math/Vector3.h"
#include"CoreSystems/Math/Vector2.h"
#include"CoreSystems/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Texture.h"
#include"Graphics/ShaderProgram.h"
#include"Graphics//VertexArrayObject.h"
#include"Graphics/Buffer.h"

/******************************
**** FOR TESTING PURPOSES *****
******************************/

#include<chrono>
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

	Graphics::ShaderProgram program;
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\VertexShader.vert", Graphics::ShaderType::VERTEX);
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\FragmentShader.frag", Graphics::ShaderType::FRAGMENT);
	program.LinkProgram();

	Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::CLAMP_BORDER, Graphics::TexWrap::CLAMP_BORDER);
	Graphics::Texture tex;
	tex.Load("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\COMMUNISM.png", config);
	tex.Bind(0);

	Vector3 vertices[6] = {
		Vector3(-1.0, -1.0, 0.0), Vector3(1.0, -1.0, 0.0),  Vector3(1.0, 1.0, 0.0),
		Vector3(-1.0, -1.0, 0.0), Vector3(1.0, 1.0, 0.0), Vector3(-1.0, 1.0, 0.0)
	};

	Vector4 colours[6]={
		Vector4(1.0,0.0,0.0,1.0), Vector4(1.0,0.0,0.0,1.0), Vector4(1.0,0.0,0.0,1.0),
		Vector4(1.0,0.0,0.0,1.0), Vector4(1.0,0.0,0.0,1.0), Vector4(1.0,0.0,0.0,1.0) 
	};

	struct mixed
	{
		Vector3 pos;
		Vector4 color;
	};

	mixed arr[6];
	arr[0].pos = Vector3(-1.0, -1.0, 0.0);
	arr[1].pos = Vector3(1.0, -1.0, 0.0);
	arr[2].pos = Vector3(1.0, 1.0, 0.0);
	arr[3].pos = Vector3(-1.0, -1.0, 0.0);
	arr[4].pos = Vector3(1.0, 1.0, 0.0);
	arr[5].pos = Vector3(-1.0, 1.0, 0.0);
	for (int i = 0; i < 6; i++)
	{
		arr[i].color = Vector4(0.5, 0.0, 0.0, 1.0);
	}

	float addedColor[6] = { 0.25,0.25,0.25,0.25,0.25,0.25 };
	Vector2 added[6]={
		Vector2(0.25, 0.0), Vector2(0.25, 0.0), Vector2(0.25, 0.0),
		Vector2(0.25, 0.0), Vector2(0.25, 0.0), Vector2(0.25, 0.0)
	};

	auto start = std::chrono::high_resolution_clock::now();
	
	VertexArrayObject vao(6);

	VertexAttributeBatch batch;
	batch.AddAttribute(0, 3, API_Type::FLOAT, 0, false);
	batch.AddAttribute(1, 4, API_Type::FLOAT, offsetof(mixed,color), false);
	vao.AddAttributeBatch(&batch);

	VertexAttributeBatch batchAddedColor;
	batchAddedColor.AddAttribute(3, 1, API_Type::FLOAT, 0, false);
	vao.AddAttributeBatch(&batchAddedColor);

	VertexAttributeBatch batchAdded;
	batchAdded.AddAttribute(2, 2, API_Type::FLOAT, 0, false);
	vao.AddAttributeBatch(&batchAdded);

	vao.PrepareAttributes();

	Buffer vbo1(sizeof(arr)+sizeof(addedColor));
	vbo1.SetData(0, sizeof(arr), arr);
	vbo1.SetData(sizeof(arr), sizeof(addedColor), addedColor);
	vao.RegisterBuffer(0, 2, 0, &vbo1);

	Buffer vbo2(sizeof(added)+50);
	vbo2.SetData(50, sizeof(added), added);
	vao.RegisterBuffer(2, 1, 50, &vbo2);

	vao.Bind();
	program.UseProgram();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	while(!window.IsClosed())
	{
		Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		/*FOR TESTING PURPOSES*/
		glDrawArrays(GL_TRIANGLES, 0, 6);
		/*********************/
		window.Update();
	}

	vbo1.Delete();
	vbo2.Delete();
	vao.Delete();
	tex.Unload();
	program.Delete();

	return 0;
}

//TODO think of a better way to delete objects than an explicit delete function!