#pragma once
#include<vector>
#include<set>
#include<glad/glad.h>

class Buffer;

enum class DataType { BYTE, UBYTE, SHORT, USHORT, INT, UINT, HALF_FLOAT, FLOAT, DOUBLE };
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
	std::vector<VertexAttributeBatch> batchList;//TODO NO pointers!
	GLuint vaoID;

public:
	VertexArrayObject();

	void AddNewAttribBatch();
	void AddExistingAttribBatch(const VertexAttributeBatch& batch);
	void AddExistingAttribBatches(const std::vector<VertexAttributeBatch>& batches);
	void AddAttribToBatch(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset); //adds to last batch

	void RegisterArrayBuffer(unsigned int firstBatchIndex, unsigned int indexCount, unsigned int numVertices, size_t attribOffset, Buffer* buffer);
	void RegisterElementBuffer(Buffer* buffer);

	void PrepareAttributes();

	void Bind();
	void Unbind();

	void Delete();
	~VertexArrayObject();

private:
	size_t SizeOfType(const DataType& type) const;
	GLenum TypeToOpenGL(DataType type) const;
};
