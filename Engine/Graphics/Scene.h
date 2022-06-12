#pragma once
#include"../Math/Vector3.h"
#include"../Math/Matrix4.h"
#include"Model.h"
#include"ShaderProgram.h"
#include<vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

namespace Graphics
{
	class SceneNode
	{
	private:
		std::vector<SceneNode*> children;
		SceneNode* parent;
		Matrix4 localTransform;
		Matrix4 worldTransform;
		int modelIndex;
		//TODO Use TRS class to create local matrix
	public:
		SceneNode(int modelIndex = -1);
		void SetParent(SceneNode* parent);
		void SetTransform(const Matrix4& transform);

		const Matrix4& GetLocalTransform() const;
		const Matrix4& GetWorldTransform() const;
		std::vector<SceneNode*>::iterator GetChildrenIteratorStart();
		std::vector<SceneNode*>::iterator GetChildrenIteratorEnd();

		void Update();
		void Draw(ShaderProgram& shaderProgram, ModelList& modelList);

		~SceneNode();
	};

	class Scene
	{
		// mesh list
		// material list
		// texture list
		// node list (scene graph)
		// lights
		// camera
	private:
		SceneNode* rootNode;
		ModelList* modelList;
	public:
		Scene();
		void SetSceneRoot(SceneNode* rootNode);
		void SetModelList(ModelList* modelList);
		void DrawScene(ShaderProgram& shaderProgram);

	private:
		void DrawNode(SceneNode* sceneNode, ShaderProgram& shaderProgram);
	};
}