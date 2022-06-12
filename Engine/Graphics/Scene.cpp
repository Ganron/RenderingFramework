#include"Scene.h"

Graphics::SceneNode::SceneNode(int modelIndex): modelIndex(modelIndex), parent(nullptr)
{
}

void Graphics::SceneNode::SetParent(SceneNode * parent)
{
	if (this->parent)
	{
		std::vector<SceneNode*>::const_iterator pos = std::find(this->parent->children.begin(), this->parent->children.end(), this);
		if (pos != this->parent->children.end())
		{
			this->parent->children.erase(pos);
		}
	}

	if (parent)
	{
		parent->children.push_back(this);
	}
	
	this->parent = parent;
}

void Graphics::SceneNode::SetTransform(const Matrix4 & transform)
{
	localTransform = transform;
}

const Matrix4 & Graphics::SceneNode::GetLocalTransform() const
{
	return localTransform;
}

const Matrix4 & Graphics::SceneNode::GetWorldTransform() const
{
	return worldTransform;
}

std::vector<Graphics::SceneNode*>::iterator Graphics::SceneNode::GetChildrenIteratorStart()
{
	return children.begin();
}

std::vector<Graphics::SceneNode*>::iterator Graphics::SceneNode::GetChildrenIteratorEnd()
{
	return children.end();
}

void Graphics::SceneNode::Update()
{
	if (parent)
	{
		worldTransform = parent->worldTransform * localTransform;
	}
	else
	{
		worldTransform = localTransform;
	}
	std::vector<SceneNode*>::iterator it = children.begin();
	for (it; it != children.end(); it++)
	{
		(*it)->Update();
	}
}

void Graphics::SceneNode::Draw(ShaderProgram & shaderProgram, ModelList & modelList)
{
	if (modelIndex >= 0)
	{
		modelList.DrawModel(modelIndex, shaderProgram);
	}
}

Graphics::SceneNode::~SceneNode()
{
}

Graphics::Scene::Scene(): rootNode(nullptr), modelList(nullptr)
{
}

void Graphics::Scene::SetSceneRoot(SceneNode * rootNode)
{
	this->rootNode = rootNode;
}

void Graphics::Scene::SetModelList(ModelList * modelList)
{
	this->modelList = modelList;
}

void Graphics::Scene::DrawScene(ShaderProgram & shaderProgram)
{
	shaderProgram.UseProgram();
	DrawNode(rootNode, shaderProgram);
	shaderProgram.StopProgram();
}

void Graphics::Scene::DrawNode(SceneNode * sceneNode, ShaderProgram& shaderProgram)
{
	shaderProgram.SetUniform(Graphics::INDEX_UNIFORM_MODEL_MATRIX, 1, &sceneNode->GetWorldTransform());
	sceneNode->Draw(shaderProgram, *modelList);

	std::vector<SceneNode*>::iterator it = rootNode->GetChildrenIteratorStart();
	for (it; it != rootNode->GetChildrenIteratorEnd(); it++)
	{
		DrawNode(*it, shaderProgram);
	}
}
