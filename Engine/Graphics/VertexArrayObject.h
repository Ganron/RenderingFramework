#pragma once
#include<vector>
#include<set>
#include<glad/glad.h>

class Buffer;

enum class DataType { BYTE, U_BYTE, SHORT, U_SHORT, INT, U_INT, HALF_FLOAT, FLOAT, DOUBLE };
enum class AttribType {FLOAT, FLOAT_NORM, DOUBLE, INT};

struct VertexAttribute
{
	unsigned int index;
	int numElements;
	DataType dataType;
	AttribType attribType;
	size_t relativeOffset;
	VertexAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset);
};

struct VertexAttributeBatch
{
	std::vector<VertexAttribute> attributes;
	void AddAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset);
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
	size_t SizeOfType(const DataType& type) const;
	GLenum TypeToOpenGL(DataType type) const;
};
