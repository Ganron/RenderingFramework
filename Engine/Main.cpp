#include"Math/Vector4.h"
#include"Math/Vector3.h"
#include"Math/Vector2.h"
#include"Math//Matrix4.h"
#include"Math/Matrix3.h"
#include"Utilities/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Camera.h"
#include"Graphics/Texture.h"
#include"Graphics/TextureManager.h"
#include"Graphics/ShaderProgram.h"
#include"Graphics/VertexArrayObject.h"
#include"Graphics/Buffer.h"
#include"Graphics/Mesh.h"
#include"Graphics/Model.h"

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

float deltaTime = 0.0f;
double lastFrame = 0.0;

void UpdateTimer();

int main()
{
	// Window setup
	Graphics::Window window(800, 600, "Test", false);

	// Shader setup
	Graphics::ShaderProgram program;
	program.AddShaderFromFile("VertexShader.vert", Graphics::ShaderType::VERTEX);
	program.AddShaderFromFile("FragmentShader.frag", Graphics::ShaderType::FRAGMENT);
	program.LinkProgram();

	//Geometry setup
	Model model("cottage_obj.obj");

	// Transformation setup
	Matrix4 modelMat1 = Matrix4::CreateTranslation(0.0f, 0.0f, -2.0f)*Matrix4::CreateRotation(DegToRad(0.0f), 0.0f, 1.0f, 0.0f)*Matrix4::CreateRotation(DegToRad(0.0f), 0.0f, 0.0f, 1.0f);
	Matrix4 modelMat2 =Matrix4::CreateRotation(DegToRad(180.0f), 0.0f, 1.0f, 0.0f)*Matrix4::CreateScale(0.1f);

	Matrix4 perspMat;
	program.SetUniform(0, 1, &modelMat2);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	// Rendering loop
	while(!window.IsClosed())
	{
		Vector4 color(0.0f, 0.5f, 0.7f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);
		glClear(GL_DEPTH_BUFFER_BIT);

		Matrix4 viewMat = window.GetCamera()->GetViewMatrix();
		program.SetUniform(1, 1, &viewMat);

		perspMat = Matrix4::CreateProjPerspSymmetric(window.GetCamera()->GetFieldOfViewAngle(), window.GetAspectRatio(), 0.1f, 1000.0f);
		program.SetUniform(2, 1, &perspMat);

		model.Draw(program);

		UpdateTimer();
		window.Update(deltaTime);
	}


	// Application termination
	model.Delete();
	Graphics::TextureManager::DeleteTextures();
	program.Delete();

	return 0;
}

//TODO think of a better way to delete objects than an explicit delete function!

void UpdateTimer()
{
	double currentFrame = glfwGetTime();
	deltaTime = (float)(currentFrame - lastFrame);
	lastFrame = currentFrame;
}
