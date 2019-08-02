#pragma once
#include<vector>
#include<set>
#include<glad/glad.h>

class VertexArrayBuffer;

enum class API_Type { BYTE, U_BYTE, SHORT, U_SHORT, INT, U_INT, HALF_FLOAT, FLOAT, DOUBLE };

struct VertexAttribute
{
	unsigned int index;
	int numElements;
	API_Type type;
	size_t offset;
	bool normalized;
	VertexAttribute(unsigned int index);
	VertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized);
	bool operator<(const VertexAttribute& attrib) const;
};
/*
class VertexArrayObject
{
private:
	std::set<VertexAttribute> attribs;
	std::vector<VertexArrayBuffer*> vboList;
	GLuint vaoID;
	unsigned int bindingPointCounter;

public:
	VertexArrayObject();

	void AddVertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized);
	void AddArrayBuffer(VertexArrayBuffer* vertexArrayBuffer);
	void SetArrayBuffers(const std::vector<VertexArrayBuffer*>& arrayBuffers);
	void PrepareVertexAttributes();
	void BindVertexArrays();

	void Bind();
	void Unbind();

	void RemoveArrayBuffers();
	void Delete();
	~VertexArrayObject();

private:
	size_t SizeOfType(const API_Type& type) const;
	GLenum TypeToOpenGL(const API_Type& type);
};
*/

struct VertexAttributeBatch
{
	std::vector<VertexAttribute> attributes;
	void AddAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized);
};

class VertexArrayObject
{
private:
	std::vector<VertexAttributeBatch*> batchList;
	std::vector<VertexArrayBuffer*> vboList;
	GLuint vaoID;
	unsigned int numVertices;

public:
	VertexArrayObject(unsigned int numverOfVertices);

	void AddAttributeBatch(VertexAttributeBatch* batch);
	void AddArrayBuffer(unsigned int firstBatchIndex, unsigned int count, VertexArrayBuffer* buffer);
	//TODO RemoveBuffer();
	void SetNumberOfVertices(unsigned int numberOfVertices);

	void PrepareAttributes();
	void RegisterBuffers();

	void Bind();
	void Unbind();

	void Delete();
	~VertexArrayObject();

private:
	size_t SizeOfType(const API_Type& type) const;
	GLenum TypeToOpenGL(API_Type type) const;
};
