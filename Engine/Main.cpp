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
	program.AddShaderFromFile(Filesystem::GetShaderPath("VertexShader.vert"), Graphics::ShaderType::VERTEX);
	program.AddShaderFromFile(Filesystem::GetShaderPath("FragmentShader.frag"), Graphics::ShaderType::FRAGMENT);
	program.LinkProgram();


	/*Graphics::Texture setup;
	Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::CLAMP_BORDER, Graphics::TexWrap::CLAMP_BORDER);
	Graphics::Texture tex;
	tex.Load("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Textures\\4096_clouds.jpg", config);
	tex.Bind(0);

	// Geometry setup
	std::vector<Vertex> vertices{
		Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(), Vector2(0.0f, 0.0f)), //front, lower-left [0]
		Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(), Vector2(1.0f, 0.0f)), //front, lower-right [1]
		Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(), Vector2(1.0f, 1.0f)), //front, upper-right [2]
		Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(), Vector2(0.0f, 1.0f)), //front, upper-left [3]

		Vertex(Vector3(-0.5f, -0.5f,-0.5f), Vector3(), Vector2(0.0f, 0.0f)), //back, lower-left [4]
		Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(), Vector2(1.0f, 0.0f)), //back, lower-right [5]
		Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(), Vector2(1.0f, 1.0f)), //back, upper-right [6]
		Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(), Vector2(0.0f, 1.0f)) }; //back, upper-left [7]

	
	std::vector<unsigned int> indices{ 
		0,1,2, 2,3,0, //front
		4,0,3, 3,7,4, //left
		5,4,7, 7,6,5, //back
		1,5,6, 6,2,1, //right
		3,2,6, 6,7,3, //top
		4,5,1, 1,0,4 //bottom
	};

	std::vector<Vector3> offsets{
		Vector3(-1.0f,-1.0f,0.0f),
		Vector3(1.0f, -1.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f),
		Vector3(-1.0f, 1.0f, 0.0f)
	};

	VertexAttributeBatch offsetBatch(1);
	offsetBatch.AddAttribute(5, 3, DataType::FLOAT, AttribType::FLOAT, 0);

	Mesh quad(vertices, indices, nullptr, offsets.size()*sizeof(Vector3));
	quad.AddAttribBatch(offsetBatch, offsets.size() * sizeof(Vector3), &offsets[0]);
	quad.SetUpMesh();*/

	Model model("D:\\Documents\\Assen\\Projects\\RenderingEngine\\Resources\\Models\\cottage_obj.obj");

	// Transformation setup
	Matrix4 modelMat1 = Matrix4::CreateTranslation(0.0f, 0.0f, -2.0f)*Matrix4::CreateRotation(DegToRad(0.0f), 0.0f, 1.0f, 0.0f)*Matrix4::CreateRotation(DegToRad(0.0f), 0.0f, 0.0f, 1.0f);
	Matrix4 modelMat2 =Matrix4::CreateRotation(DegToRad(180.0f), 0.0f, 1.0f, 0.0f)*Matrix4::CreateScale(0.1f);
	//Matrix4 viewMat = Matrix4::CreateTranslation(0.0f, 0.0f, -50.0f);

	Matrix4 perspMat;
	program.SetUniform(0, 1, &modelMat2);
	
	program.UseProgram();
	
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

		//quad.Draw(4);
		model.Draw();

		UpdateTimer();
		window.Update(deltaTime);
	}


	// Application termination
	//quad.Delete();
	model.Delete();
	Graphics::TextureManager::DeleteTextures();
	//tex.Unload();
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
