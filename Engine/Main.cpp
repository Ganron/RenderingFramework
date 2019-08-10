#include"CoreSystems/Math/Vector4.h"
#include"CoreSystems/Math/Vector3.h"
#include"CoreSystems/Math/Vector2.h"
#include"CoreSystems//Math//Matrix4.h"
#include"CoreSystems/Math/Matrix3.h"
#include"CoreSystems/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Texture.h"
#include"Graphics/ShaderProgram.h"
#include"Graphics//VertexArrayObject.h"
#include"Graphics/Buffer.h"
#include"Graphics/Mesh.h"

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
	// Window setup
	Graphics::Window window(800, 600, "Test", false);


	// Shader setup
	Graphics::ShaderProgram program;
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\VertexShader.vert", Graphics::ShaderType::VERTEX);
	program.AddShaderFromFile("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Shaders\\FragmentShader.frag", Graphics::ShaderType::FRAGMENT);
	program.LinkProgram();


	//Texture setup
	Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::CLAMP_BORDER, Graphics::TexWrap::CLAMP_BORDER);
	Graphics::Texture tex;
	tex.Load("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Garrus.jpg", config);


	// Geometry setup
	std::vector<Vertex> vertices{
		Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)), //front, lower-left [4]
		Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f)), //front, lower-right [5]
		Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f)), //front, upper-right [6]
		Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 1.0f)), //front, upper-left [7]

		Vertex(Vector3(-0.5f, -0.5f,-0.5f), Vector2(0.0f, 0.0f)), //back, lower-left [0]
		Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f)), //back, lower-right [1]
		Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)), //back, upper-right [2]
		Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f)) }; //back, upper-left [3]

	
	std::vector<unsigned int> indices{ 
		0,1,2, 2,3,0, //front
		4,0,3, 3,7,4, //left
		5,4,7, 7,6,5, //back
		1,5,6, 6,2,1, //right
		3,2,6, 6,7,3, //top
		4,5,1, 1,0,4 //bottom
	};

	struct colorTest
	{
		Vector3 color1;
		Vector3 color2;
	};

	colorTest color[8];
	for (int i = 0; i < 8; i++)
	{
		color[i].color1 = Vector3(0.5f, 0.0f, 0.0f);
		color[i].color2 = Vector3(0.5f, 0.0f, 0.0f);
	}

	Vector3 color2[8] = {
		Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f),
		Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f),Vector3(-0.5f, 0.0f, 0.0f)
	};

	VertexAttributeBatch colorBatch;
	colorBatch.AddAttribute(2, 3, DataType::FLOAT, AttribType::FLOAT, 0);
	colorBatch.AddAttribute(5, 3, DataType::FLOAT, AttribType::FLOAT, offsetof(colorTest, color2));

	VertexAttributeBatch colorBatch2;
	colorBatch2.AddAttribute(3, 3, DataType::FLOAT, AttribType::FLOAT, 0);

	Mesh quad(vertices, indices, sizeof(color) + sizeof(color2));
	quad.AddAdditionalAttribBatch(colorBatch, sizeof(color), color);
	quad.AddAdditionalAttribBatch(colorBatch2, sizeof(color2), color2);
	quad.SetUpMesh();


	// Transformation setup
	Matrix4 modelMat = Matrix4::CreateTranslation(0.0f, 0.0f, -2.0f)*Matrix4::CreateRotation(DegToRad(30.0f), 1.0f, 0.0f, 0.0f)*Matrix4::CreateRotation(DegToRad(25.0f), 0.0f, 1.0f, 0.0f);
	Matrix4 perspMat;
	program.SetUniform(0, 1, &modelMat);

	
	tex.Bind(0);
	program.UseProgram();
	

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	// Rendering loop
	while(!window.IsClosed())
	{
		Vector4 color(0.0f, 1.0f, 0.0f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);

		perspMat = Matrix4::CreateProjPerspSymmetric(DegToRad(90.0f), window.GetAspectRatio(), 0.1f, 1000.0f);
		program.SetUniform(1, 1, &perspMat);

		quad.Draw(1);
		window.Update();
	}


	// Application termination
	quad.Delete();
	tex.Unload();
	program.Delete();

	return 0;
}

//TODO think of a better way to delete objects than an explicit delete function!