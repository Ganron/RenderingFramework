#include"Math/Vector4.h"
#include"Math/Vector3.h"
#include"Math/Vector2.h"
#include"Math//Matrix4.h"
#include"Math/Matrix3.h"
#include"Utilities/FileSystem.h"
#include"Graphics/Window.h"
#include"Graphics/Camera.h"
#include"Graphics/Texture.h"
#include"Graphics/ShaderProgram.h"
#include"Graphics/VertexArrayObject.h"
#include"Graphics/Buffer.h"
#include"Graphics/Mesh.h"
#include"Graphics/Material.h"
#include"Graphics/Model.h"
#include"Graphics/Lights.h"
#include"Graphics/ResourceLoader.h"

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
	/*
	 * WINDOW SETUP
	 */
	Graphics::Window window(800, 600, "Test", false);

	/*
	 * SHADER SETUP
	 */
	Graphics::ShaderProgram blinnPhong;
	blinnPhong.AddShaderFromFile("BlinnPhong.vert", Graphics::ShaderType::VERTEX);
	blinnPhong.AddShaderFromFile("BlinnPhong.frag", Graphics::ShaderType::FRAGMENT);
	blinnPhong.LinkProgram();

	Graphics::ShaderProgram lightCubes;
	lightCubes.AddShaderFromFile("Cube.vert", Graphics::ShaderType::VERTEX);
	lightCubes.AddShaderFromFile("Cube.frag", Graphics::ShaderType::FRAGMENT);
	lightCubes.LinkProgram();


	/*
	 * GEOMETRY SETUP
	 */
	
	Graphics::TextureList texList;
	Graphics::MaterialList matList(texList);
	Graphics::MeshList meshList;
	Graphics::ModelList modelList(meshList, matList);

	Graphics::ResourceLoader::LoadModel("cottage_obj.obj", modelList);
	Graphics::ResourceLoader::LoadModel("Street Lamp.obj", modelList);
	Graphics::ResourceLoader::LoadModel("Tree2_final.obj", modelList);

	//Cottage model
	int cottageIndex = meshList.GetMeshIndex("Cube_Cube.002");
	int cottageMatIndex = modelList.GetModel("cottage_obj.obj").GetMatIndexOfMesh(cottageIndex);

	std::vector<Graphics::MeshMatPair> cottageIndices{
		{
			cottageIndex,
			cottageMatIndex
		}
	};
	int modelCottage = modelList.CreateModel("Cottage", cottageIndices);

	//Tree model
	const Graphics::Model& tree = modelList.GetModel("Tree2_final.obj");
	int treeTrunkIndex = meshList.GetMeshIndex("tree.002_Mesh.001");
	int treeTrunkMatIndex = tree.GetMatIndexOfMesh(treeTrunkIndex);
	int treeLeavesIndex = meshList.GetMeshIndex("leaves.002_leaves.004");
	int treeLeavesMatIndex = tree.GetMatIndexOfMesh(treeLeavesIndex);

	std::vector<Graphics::MeshMatPair> treeIndices{
		{treeTrunkIndex, treeTrunkMatIndex},
		{treeLeavesIndex,treeLeavesMatIndex}
	};

	int modelTree = modelList.CreateModel("Tree", treeIndices);

	//Plane model
	std::vector<Graphics::Vertex> planeVertices{
		{Vector3(-63.196327, 0.077648, 63.196327), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f)},
		{Vector3{63.196327, 0.077648, 63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(10.0f, 0.0f)},
		{Vector3{-63.196327, 0.077648, -63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(10.0f, 10.0f)}, //swapped
		{Vector3{63.196327, 0.077648, -63.196327}, Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 10.0f)} //swapped
	};

	std::vector<unsigned int> planeIndices{ 0,1,3, 3,2,0 };

	int planeIndex = meshList.CreateMesh("Plane", planeVertices, planeIndices);
	unsigned int planeTexIndex = texList.LoadFromFile("grass-lawn-texture.jpg");
	int planeMatIndex = matList.CreateMaterial(
		"Grass",
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(0.64f, 0.64f, 0.64f),
		Vector3(0.1f, 0.1f, 0.1f),
		1.0f,
		std::vector<unsigned int>{planeTexIndex}
	);

	std::vector<Graphics::MeshMatPair> planeMeshMatPair{
		{planeIndex, planeMatIndex}
	};

	int modelPlane = modelList.CreateModel("Plane", planeMeshMatPair);


	/*
	 * TRANSFORMATION SETUP
	 */
	Matrix4 modelMat1 = Matrix4::CreateRotation(DegToRad(90.0f), 0.0f, 1.0f, 0.0f) * Matrix4::CreateScale(0.1f);
	Matrix4 modelMat2 = Matrix4::CreateTranslation(2.5f, 0.45f, 1.7f) * Matrix4::CreateRotation(DegToRad(-90.0f), 0.0f, 1.0f, 0.0f) * Matrix4::CreateScale(0.001f);
	Matrix4 modelMat3 = Matrix4::CreateTranslation(1.0f, 0.45f, 2.5f) * Matrix4::CreateRotation(DegToRad(180.0f), 0.0f, 1.0f, 0.0f) * Matrix4::CreateScale(0.001f);

	Matrix4 trees[15];
	trees[0] = Matrix4::CreateTranslation(2.0f, 0.0f, -0.15f) * Matrix4::CreateScale(0.11f);
	trees[1] = Matrix4::CreateTranslation(1.73f, 0.0f, 0.74f) * Matrix4::CreateScale(0.11f);
	trees[2] = Matrix4::CreateTranslation(2.3f, 0.0f, 2.5f) * Matrix4::CreateScale(0.11f);
	trees[3] = Matrix4::CreateTranslation(-4.5f, 0.0f, -3.67f) * Matrix4::CreateScale(0.11f);
	trees[4] = Matrix4::CreateTranslation(-2.50, 0.0f, -3.18f) * Matrix4::CreateScale(0.11f);
	trees[5] = Matrix4::CreateTranslation(-1.81f, 0.0f, -2.22f) * Matrix4::CreateScale(0.11f);
	trees[6] = Matrix4::CreateTranslation(-3.72f, 0.0f, -1.35f) * Matrix4::CreateScale(0.11f);
	trees[7] = Matrix4::CreateTranslation(-2.66f, 0.0f, -2.05f) * Matrix4::CreateScale(0.11f);
	trees[8] = Matrix4::CreateTranslation(-3.39f, 0.0f, 1.15f) * Matrix4::CreateScale(0.11f);
	trees[9] = Matrix4::CreateTranslation(-2.14f, 0.0f, -0.5f) * Matrix4::CreateScale(0.11f);
	trees[10] = Matrix4::CreateTranslation(-1.14f, 0.0f, -0.21f) * Matrix4::CreateScale(0.11f);
	trees[11] = Matrix4::CreateTranslation(-2.42f, 0.0f, 2.19f) * Matrix4::CreateScale(0.11f);
	trees[12] = Matrix4::CreateTranslation(-1.5f, 0.0f, 1.0f) * Matrix4::CreateScale(0.11f);
	trees[13] = Matrix4::CreateTranslation(-1.1f, 0.0f, 3.5f) * Matrix4::CreateScale(0.11f);
	trees[14] = Matrix4::CreateTranslation(-1.42f, 0.0f, 3.0f) * Matrix4::CreateScale(0.11f);

	Matrix4 perspMat;

	/*
	 * LIGHT SETUP
	 */
	std::vector<Vector3> lightPositions{
		{2.5f, 3.0f, 5.0f},
		{0.4f, 1.55f, 2.5f},
		{0.0f, 1.0f, 3.0f}
	};

	Graphics::DirectionalLight dirLight;
	dirLight.direction = { 0.0f, -1.0f, -1.0f };
	dirLight.ambientColor = Vector3(0.7f, 0.8f, 1.0f) * 0.3f;
	dirLight.diffuseColor = Vector3(1.0f, 0.9f, 0.7f);
	dirLight.specularColor = Vector3(1.0f, 0.9f, 0.7f);
	//dirLight.SetInShader(blinnPhong);

	Graphics::DirectionalLight dirLight2;
	dirLight.direction = { 0.0f, -1.0f, -1.0f };
	dirLight.ambientColor = Vector3(0.15f);
	dirLight.diffuseColor = Vector3(0.337f, 0.7f, 0.984f) * 0.15f;
	dirLight.specularColor = Vector3(0.337f, 0.7f, 0.984f) * 0.15f;
	//dirLight.SetInShader(blinnPhong);

	Graphics::PointLight pointLight1;
	pointLight1.position = lightPositions[0];
	pointLight1.ambientColor = Vector3(0.35f);
	pointLight1.diffuseColor = Vector3(0.337f, 0.7f, 0.984f);
	pointLight1.specularColor = Vector3(1.0f);
	pointLight1.constCoeff = 1.0f;
	pointLight1.linearCoeff = 0.14f;
	pointLight1.quadraticCoeff = 0.07f;


	Graphics::PointLight pointLight2 = pointLight1;
	pointLight2.position = lightPositions[0];

	Graphics::PointLight pointLight3 = pointLight1;
	pointLight3.position = lightPositions[2];

	Buffer pointLightBuffer(Graphics::MAX_POINT_LIGHTS * sizeof(Graphics::PointLight) + sizeof(int));
	pointLightBuffer.SetData(0, sizeof(pointLight1), &pointLight1);
	pointLightBuffer.SetData(sizeof(pointLight1), sizeof(pointLight2), &pointLight2);
	pointLightBuffer.SetData(sizeof(pointLight1) + sizeof(pointLight2), sizeof(pointLight3), &pointLight3);
	int numPointLights = 1;
	pointLightBuffer.SetData(Graphics::MAX_POINT_LIGHTS * sizeof(Graphics::PointLight), sizeof(int), &numPointLights);
	pointLightBuffer.BindUniform(0, 0, pointLightBuffer.GetSize());


	Graphics::SpotLight spotLight;
	spotLight.ambientColor = Vector3(0.5f);
	spotLight.diffuseColor = Vector3(0.9f, 1.0f, 0.8f) * 1.3;
	spotLight.specularColor = Vector3(1.0f);
	spotLight.constCoeff = 1.0f;
	spotLight.linearCoeff = 0.14f;
	spotLight.quadraticCoeff = 0.07f;
	spotLight.innerConeAngle = DegToRad(5.0f);
	spotLight.outerConeAngle = DegToRad(15.0f);

	Graphics::SpotLight spotLight1;
	spotLight1.position = lightPositions[1];
	spotLight1.direction = Vector3(0.0f, -1.0f, 0.0f);
	spotLight1.ambientColor = Vector3(1.0f);
	spotLight1.diffuseColor = Vector3(1, 0.784, 0.019);
	spotLight1.specularColor = Vector3(1.0f);
	spotLight1.constCoeff = 1.0f;
	spotLight1.linearCoeff = 0.7f;
	spotLight1.quadraticCoeff = 1.8f;
	spotLight1.innerConeAngle = DegToRad(20.0f);
	spotLight1.outerConeAngle = DegToRad(35.0f);

	Graphics::SpotLight spotLight2 = spotLight1;
	spotLight2.position = lightPositions[1];

	Buffer spotLightBuffer(Graphics::MAX_SPOT_LIGHTS * sizeof(Graphics::SpotLight) + sizeof(int));
	int numSpotLights = 2;
	spotLightBuffer.SetData(sizeof(spotLight), sizeof(spotLight1), &spotLight1);
	spotLightBuffer.SetData(sizeof(spotLight) + sizeof(spotLight1), sizeof(spotLight2), &spotLight2);
	spotLightBuffer.SetData(Graphics::MAX_SPOT_LIGHTS * sizeof(Graphics::SpotLight), sizeof(int), &numSpotLights);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	for (int i = 0; i < meshList.GetNumMeshes(); i++)
	{
		std::cout << "MESH #" << i << " " << meshList[i].GetName() << std::endl;
	}

	for (int i = 0; i < matList.GetNumMaterials(); i++)
	{
		std::cout << "MATERIAL #" << i << " " << matList[i].GetName() << std::endl;
	}

	for (int i = 0; i < modelList.GetNumModels(); i++)
	{
		const Graphics::Model& currentModel = modelList[i];
		std::cout << "MODEL #" << i << " " << currentModel.GetName() << std::endl;
		std::vector<Graphics::MeshMatPair>::const_iterator pair = currentModel.GetMeshMatPairStart();
		for (pair; pair != currentModel.GetMeshMatPairEnd(); pair++)
		{
			std::cout << " Mesh Index:" << pair->meshIndex << " Mat Index:" << pair->matIndex << std::endl;
		}
	}

	for (int i = 0; i < texList.GetNumTextures(); i++)
	{
		std::cout << "TEX #" << i << " " << texList[i].GetName() << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Rendering loop

	while (!window.IsClosed())
	{
		Vector4 color(0.019f, 0.070f, 0.137f, 1.0f);
		glClearBufferfv(GL_COLOR, NULL, &color[0]);
		glClear(GL_DEPTH_BUFFER_BIT);

		blinnPhong.StopProgram();

		//Setting up view matrix
		Matrix4 viewMat = window.GetCamera()->GetViewMatrix();
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_VIEW_MATRIX, 1, &viewMat);
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_VIEW_MATRIX, 1, &viewMat);

		//Setting up proj matrix
		perspMat = Matrix4::CreateProjPerspSymmetric(window.GetCamera()->GetFieldOfViewAngle(), window.GetAspectRatio(), 0.1f, 1000.0f);
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_PROJ_MATRIX, 1, &perspMat);
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_PROJ_MATRIX, 1, &perspMat);

		//Updating flashlight
		spotLight.position = window.GetCamera()->GetPosition();
		spotLight.direction = window.GetCamera()->GetForwardDirection();
		spotLightBuffer.SetData(0, sizeof(spotLight), &spotLight);
		spotLightBuffer.BindUniform(1, 0, spotLightBuffer.GetSize());

		blinnPhong.UseProgram();

		//Drawing: street lamp
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &modelMat3);
		modelList.DrawModel(modelList.GetModelIndex("Street Lamp.obj"), blinnPhong);

		//Drawing: cottage
		blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &modelMat1);
		modelList.DrawModel(modelCottage, blinnPhong);

		//Drawing: plane
		modelList.DrawModel(modelPlane, blinnPhong);

		//Drawing: trees
		for (int i = 0; i < 15; i++)
		{
			blinnPhong.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &trees[i]);
			modelList.DrawModel(modelTree, blinnPhong);
		}

		/*
		lightCubes.UseProgram();
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_VIEW_MATRIX, 1, &viewMat);
		lightCubes.SetUniform(Graphics::INDEX_UNIFORM_PROJ_MATRIX, 1, &perspMat);

		for (int i = 0; i < 3; i++)
		{
			Matrix4 lightModelMat = Matrix4::CreateTranslation(lightPositions[i]) * Matrix4::CreateScale(0.1f);
			lightCubes.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &lightModelMat);
			modelList.DrawModel(0, lightCubes);
		}*/

		UpdateTimer();
		window.Update(deltaTime);
	}


	// Application termination
	texList.ClearList();
	matList.ClearList();
	meshList.ClearList();
	modelList.ClearList();
	pointLightBuffer.Delete();
	spotLightBuffer.Delete();
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
