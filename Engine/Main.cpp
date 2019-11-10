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
#include"Graphics//Lights.h"

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
	Graphics::ShaderProgram blinnPhong;
	blinnPhong.AddShaderFromFile("BlinnPhong.vert", Graphics::ShaderType::VERTEX);
	blinnPhong.AddShaderFromFile("BlinnPhong.frag", Graphics::ShaderType::FRAGMENT);
	blinnPhong.LinkProgram();

	Graphics::ShaderProgram lightCubes;
	lightCubes.AddShaderFromFile("Cube.vert", Graphics::ShaderType::VERTEX);
	lightCubes.AddShaderFromFile("Cube.frag", Graphics::ShaderType::FRAGMENT);
	lightCubes.LinkProgram();

	// Geometry setup
	Graphics::TextureManager texManager;
	Graphics::Model model("cottage_obj.obj", texManager);
	Graphics::Model streetlight("Street Lamp.obj", texManager);
	Graphics::Model tree("Tree1.obj", texManager);

	std::vector<Graphics::Vertex> vertices{
		{ Vector3(-1.0f, -1.0f,  1.0f)},
		{ Vector3(1.0f, -1.0f,  1.0f)},
		{ Vector3(1.0f,  1.0f,  1.0f)},
		{ Vector3(-1.0f,  1.0f,  1.0f)},

		{ Vector3(-1.0, -1.0, -1.0) },
		{ Vector3(1.0, -1.0, -1.0) },
		{ Vector3(1.0,  1.0, -1.0) },
		{ Vector3(-1.0,  1.0, -1.0)}
	};

	std::vector<unsigned int> indices{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
	
	Graphics::Mesh cube(vertices, indices, -1);
	cube.SetUpMesh();

	std::vector<Graphics::Vertex> planeVertices{
		{Vector3(-63.196327, 0.077648, 63.196327), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f)},
		{Vector3{63.196327, 0.077648, 63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(10.0f, 0.0f)},
		{Vector3{-63.196327, 0.077648, -63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(10.0f, 10.0f)}, //swapped
		{Vector3{63.196327, 0.077648, -63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 10.0f)} //swapped
	};

	std::vector<unsigned int> planeIndices{ 0,1,3, 3,2,0 };

	Graphics::Mesh plane(planeVertices, planeIndices, -1);
	plane.SetUpMesh();
	Graphics::Texture tex;
	tex.LoadFromFile("grass-lawn-texture.jpg");
	Graphics::Material mat;
	mat.ambientColor = Vector3(1.000000, 1.000000, 1.000000);
	mat.diffuseColor = Vector3(0.640000, 0.640000, 0.640000);
	mat.specularColor = Vector3(0.100000, 0.100000, 0.100000);
	mat.specularExponent = 1.0;

	// Transformation setup
	Matrix4 modelMat1 = Matrix4::CreateRotation(DegToRad(90.0f), 0.0f, 1.0f, 0.0f)*Matrix4::CreateScale(0.1f);
	Matrix4 modelMat2 = Matrix4::CreateTranslation(2.5f, 0.45f, 1.7f) * Matrix4::CreateRotation(DegToRad(-90.0f),0.0f,1.0f,0.0f) * Matrix4::CreateScale(0.001f);
	Matrix4 modelMat3 = Matrix4::CreateTranslation(-2.5f, 0.45f, 1.7f) * Matrix4::CreateRotation(DegToRad(-90.0f), 0.0f, 1.0f, 0.0f) * Matrix4::CreateScale(0.001f);

	std::vector<Vector3> lightPositions{
		{ 2.5f, 1.55f, 2.2f},
		{-2.5f, 1.55f, 2.2f},
		{0.0f, 1.0f, 3.0f}
	};

	Matrix4 perspMat;

	// Ligh setup
	Graphics::DirectionalLight dirLight;
	dirLight.direction = (0.0f, -1.0f, -1.0f);
	dirLight.ambientColor = Vector3(0.7f, 0.8f, 1.0f)*0.3f;
	dirLight.diffuseColor = Vector3(1.0f, 0.9f, 0.7f);
	dirLight.specularColor = Vector3(1.0f, 0.9f, 0.7f);
	dirLight.SetInShader(blinnPhong);

	Graphics::PointLight pointLight1;
	pointLight1.position = lightPositions[0];
	pointLight1.ambientColor = 0.35f;
	pointLight1.diffuseColor = Vector3(0.337f,0.7f,0.984f);
	pointLight1.specularColor = 1.0f;
	pointLight1.constCoeff = 1.0f;
	pointLight1.linearCoeff = 0.7f;
	pointLight1.quadraticCoeff = 1.8f;


	Graphics::PointLight pointLight2 = pointLight1;
	pointLight2.position = lightPositions[1];

	Graphics::PointLight pointLight3 = pointLight1;
	pointLight3.position = lightPositions[2];

	Buffer pointLightBuffer(Graphics::MAX_POINT_LIGHTS * sizeof(Graphics::PointLight) + sizeof(int));
	pointLightBuffer.SetData(0, sizeof(pointLight1), &pointLight1);
	pointLightBuffer.SetData(sizeof(pointLight1), sizeof(pointLight2), &pointLight2);
	pointLightBuffer.SetData(sizeof(pointLight1) + sizeof(pointLight2), sizeof(pointLight3), &pointLight3);
	int numPointLights = 0;
	pointLightBuffer.SetData(Graphics::MAX_POINT_LIGHTS * sizeof(Graphics::PointLight), sizeof(int), &numPointLights);
	pointLightBuffer.BindUniform(0, 0, pointLightBuffer.GetSize());


	Graphics::SpotLight spotLight;
	spotLight.ambientColor = 0.2f;
	spotLight.diffuseColor = Vector3(0.9f, 1.0f, 0.8f);
	spotLight.specularColor = 1.0f;
	spotLight.constCoeff = 1.0f;
	spotLight.linearCoeff = 0.14f;
	spotLight.quadraticCoeff = 0.07f;
	spotLight.innerConeAngle = DegToRad(10.0f);
	spotLight.outerConeAngle = DegToRad(35.0f);

	Graphics::SpotLight spotLight1;
	spotLight1.position = lightPositions[0];
	spotLight1.direction = Vector3(0.0f, -1.0f, 0.0f);
	spotLight1.ambientColor = 0.35f;
	spotLight1.diffuseColor = Vector3(1, 0.784, 0.019);
	spotLight1.specularColor = 1.0f;
	spotLight1.constCoeff = 1.0f;
	spotLight1.linearCoeff = 0.7f;
	spotLight1.quadraticCoeff = 1.8f;
	spotLight1.innerConeAngle = DegToRad(30.0f);
	spotLight1.outerConeAngle = DegToRad(60.0f);

	Graphics::SpotLight spotLight2 = spotLight1;
	spotLight2.position = lightPositions[1];

	Buffer spotLightBuffer(Graphics::MAX_SPOT_LIGHTS * sizeof(Graphics::SpotLight) + sizeof(int));
	int numSpotLights = 0;
	spotLightBuffer.SetData(sizeof(spotLight), sizeof(spotLight1), &spotLight1);
	spotLightBuffer.SetData(sizeof(spotLight) + sizeof(spotLight1), sizeof(spotLight2), &spotLight2);
	spotLightBuffer.SetData(Graphics::MAX_SPOT_LIGHTS * sizeof(Graphics::SpotLight), sizeof(int), &numSpotLights);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Rendering loop
	while(!window.IsClosed())
	{
		//Vector4 color(0.0f, 0.5f, 0.7f, 1.0f);
		Vector4 color(0.019f, 0.070f, 0.137f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);
		glClear(GL_DEPTH_BUFFER_BIT);

		Matrix4 viewMat = window.GetCamera()->GetViewMatrix();
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_VIEW_MATRIX, 1, &viewMat);
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_VIEW_MATRIX, 1, &viewMat);
		
		perspMat = Matrix4::CreateProjPerspSymmetric(window.GetCamera()->GetFieldOfViewAngle(), window.GetAspectRatio(), 0.1f, 1000.0f);
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_PROJ_MATRIX, 1, &perspMat);
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_PROJ_MATRIX, 1, &perspMat);

		spotLight.position = window.GetCamera()->GetPosition();
		spotLight.direction = window.GetCamera()->GetForwardDirection();
		spotLightBuffer.SetData(0, sizeof(spotLight), &spotLight);
		spotLightBuffer.BindUniform(1, 0, spotLightBuffer.GetSize());

		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &modelMat2);
		streetlight.Draw(blinnPhong);

		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &modelMat3);
		streetlight.Draw(blinnPhong);

		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &modelMat1);
		//model.DrawMesh(0,blinnPhong);
		model.DrawMesh(4,blinnPhong);

		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL, 1, &(mat.ambientColor));
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 1, 1, &(mat.diffuseColor));
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 2, 1, &(mat.specularColor));
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 3, 1, &(mat.specularExponent));
		tex.Bind(0);
		plane.Draw();
		tex.Unbind();
		

		tree.DrawMesh(0,blinnPhong);
		/*for (int i = 0; i < 3; i++)
		{
			Matrix4 lightModelMat = Matrix4::CreateTranslation(lightPositions[i]) * Matrix4::CreateScale(0.1f);
			lightCubes.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &lightModelMat);
			lightCubes.UseProgram();
			cube.Draw();
		}*/

		UpdateTimer();
		window.Update(deltaTime);
	}

	
	// Application termination
	plane.Delete();
	tex.Delete();
	model.Delete();
	streetlight.Delete();
	cube.Delete();
	tree.Delete();
	pointLightBuffer.Delete();
	spotLightBuffer.Delete();
	texManager.DeleteTextures();
	blinnPhong.Delete();
	lightCubes.Delete();

	return 0;
}

//TODO think of a better way to delete objects than an explicit delete function!

void UpdateTimer()
{
	double currentFrame = glfwGetTime();
	deltaTime = (float)(currentFrame - lastFrame);
	lastFrame = currentFrame;
}
