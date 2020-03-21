#pragma once
#include<vector>
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

class VertexAttributeBatch
{
private:
	std::vector<VertexAttribute> attributes;
public:
	VertexAttributeBatch();

	void AddAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset);

	std::vector<VertexAttribute>::const_iterator GetIteratorStart() const;
	std::vector<VertexAttribute>::const_iterator GetIteratorEnd() const;
};

class VertexArrayObject
{
private:
	std::vector<VertexAttributeBatch> batchList;
	GLuint vaoID;

public:
	VertexArrayObject();

	void StartNewAttribBatch();
	void AddExistingAttribBatch(const VertexAttributeBatch& batch);
	void AddExistingAttribBatches(const std::vector<VertexAttributeBatch>& batches);
	void AddAttribToBatch(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset); //adds to last batch

	void RegisterArrayBuffer(unsigned int firstBatchIndex, unsigned int indexCount, unsigned int numVertices, size_t attribOffset, Buffer* buffer);
	void RegisterElementBuffer(Buffer* buffer) const;
	void UnregisterBuffers() const;

	void PrepareAttributes();

	size_t GetNumberOfBatches() const;

	void Bind() const;
	void Unbind() const;

	void Delete();
	~VertexArrayObject();

private:
	size_t SizeOfType(const DataType& type) const;
	GLenum TypeToOpenGL(DataType type) const;
};
