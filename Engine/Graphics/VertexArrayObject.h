#pragma once
#include<vector>
#include<set>
#include<glad/glad.h>

class Buffer;

enum class API_Type { BYTE, U_BYTE, SHORT, U_SHORT, INT, U_INT, HALF_FLOAT, FLOAT, DOUBLE };

struct VertexAttribute
{
	unsigned int index;
	int numElements;
	API_Type type;
	size_t offset;
	bool normalized;
	VertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized);
};

struct VertexAttributeBatch
{
	std::vector<VertexAttribute> attributes;
	void AddAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized);
};

class VertexArrayObject
{
private:
	std::vector<VertexAttributeBatch*> batchList;	
	GLuint vaoID;
	unsigned int numVertices;

public:
	VertexArrayObject(unsigned int numberOfVertices);

	void AddAttributeBatch(VertexAttributeBatch* batch);
	void RegisterBuffer(unsigned int firstBatchIndex, unsigned int indexCount, size_t attribOffset, Buffer* buffer);
	void SetNumberOfVertices(unsigned int numberOfVertices);

	void PrepareAttributes();

	void Bind();
	void Unbind();

	void Delete();
	~VertexArrayObject();

private:
	size_t SizeOfType(const API_Type& type) const;
	GLenum TypeToOpenGL(API_Type type) const;
};
