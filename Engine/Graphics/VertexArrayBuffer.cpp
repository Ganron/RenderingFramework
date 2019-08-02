#include"VertexArrayBuffer.h"
#include<iostream>
/*
VertexArrayBuffer::VertexArrayBuffer(size_t bufferSize, size_t attribOffset, unsigned int numberOfVertices, bool interleaved) :
	size(bufferSize), initialOffset(attribOffset), numVertices(numberOfVertices), interleaved(interleaved)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, NULL, GL_DYNAMIC_STORAGE_BIT);
}

VertexArrayBuffer::VertexArrayBuffer(size_t bufferSize, size_t attribOffset, unsigned int numberOfVertices, bool interleaved, const void * data) :
	size(bufferSize), initialOffset(attribOffset), numVertices(numberOfVertices), interleaved(interleaved)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, data, GL_DYNAMIC_STORAGE_BIT);
}

void VertexArrayBuffer::AddAttribIndex(int attribIndex)
{
	attribIndices.push_back(attribIndex);
}

void VertexArrayBuffer::SetAttribIndices(const int * indicesList, int count)
{
	for (int i = 0; i < count; i++)
	{
		attribIndices.push_back(indicesList[i]);
	}
}

void VertexArrayBuffer::SetAttribIndices(std::vector<int>& indicesList)
{
	attribIndices = indicesList;
}

//TODO check capacity
void VertexArrayBuffer::SetData(int offset, int size, const void* data)
{
	glNamedBufferSubData(bufferID, offset, size, data);
}

const std::vector<int>& VertexArrayBuffer::GetAttribIndices() const
{
	return attribIndices;
}

GLuint VertexArrayBuffer::GetBufferID() const
{
	return bufferID;
}

size_t VertexArrayBuffer::GetSize() const
{
	return size;
}

size_t VertexArrayBuffer::GetInitialOffset() const
{
	return initialOffset;
}

unsigned int VertexArrayBuffer::GetNumberOfVertices() const
{
	return numVertices;
}

bool VertexArrayBuffer::InterleavedAttribs() const
{
	return interleaved;
}

void VertexArrayBuffer::Delete()
{
	glDeleteBuffers(1, &bufferID);
}

VertexArrayBuffer::~VertexArrayBuffer()
{
}
*/

VertexArrayBuffer::VertexArrayBuffer(size_t bufferSize, size_t attribOffset) :size(bufferSize), initialOffset(attribOffset)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, NULL, GL_DYNAMIC_STORAGE_BIT);
}

VertexArrayBuffer::VertexArrayBuffer(size_t bufferSize, size_t attribOffset, const void * data) :size(bufferSize), initialOffset(attribOffset)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, data, GL_DYNAMIC_STORAGE_BIT);
}

void VertexArrayBuffer::AssignAttribBatchIndices(unsigned int first, unsigned int count)
{
	firstBatchIndex = first;
	batchIndexCount = count;
}

void VertexArrayBuffer::SetData(int offset, int size, const void * data)
{
	glNamedBufferSubData(bufferID, offset, size, data);
}

GLuint VertexArrayBuffer::GetBufferID() const
{
	return bufferID;
}

size_t VertexArrayBuffer::GetSize() const
{
	return size;
}

size_t VertexArrayBuffer::GetInitialOffset() const
{
	return initialOffset;
}

unsigned int VertexArrayBuffer::GetFirstAttribBatchIndex() const
{
	return firstBatchIndex;
}

unsigned int VertexArrayBuffer::GetAttribBatchIndexCount() const
{
	return batchIndexCount;
}

void VertexArrayBuffer::Delete()
{
	glDeleteBuffers(1, &bufferID);
}

VertexArrayBuffer::~VertexArrayBuffer()
{
}
