#pragma once
#include<vector>
#include<glad/glad.h>

/* NOTES FOR DEVELOPMENT PURPOSES
Buffer params:
	-size;
	-purpose;

Attrib params:
	-attrib index;
	-binding index;
	
	Format:
		-size(#elements);
		-type;
		-normalized;
		-offset(relative to the start of the vertex);

	Storage:
		-offset(of the first vertex, relative to the start of the buffer);
		-stride; - size of vertex

*/

/*
class VertexArrayBuffer
{
private:
	std::vector<int> attribIndices;
	GLuint bufferID;
	size_t size;
	size_t initialOffset;
	unsigned int numVertices;
	bool interleaved;//TODO allow for a mixed attribute arrangement?
	
public:
	VertexArrayBuffer(size_t bufferSize, size_t attribOffset, unsigned int numberOfVertices, bool interleaved);
	VertexArrayBuffer(size_t bufferSize, size_t attribOffset, unsigned int numberOfVertices, bool interleaved, const void* data);

	void AddAttribIndex(int attribIndex);
	void SetAttribIndices(const int* indicesList, int count);
	void SetAttribIndices(std::vector<int>& indicesList);
	void SetData(int offset, int size, const void* data);

	const std::vector<int>& GetAttribIndices() const;
	GLuint GetBufferID() const;
	size_t GetSize() const;
	size_t GetInitialOffset() const;
	unsigned int GetNumberOfVertices() const;
	bool InterleavedAttribs() const;

	void Delete();
	~VertexArrayBuffer();
	
};*/

class VertexArrayBuffer 
{
private:
	//std::vector<int> attribBatchIndices;
	unsigned int firstBatchIndex;
	unsigned int batchIndexCount;
	GLuint bufferID;
	size_t size;
	size_t initialOffset;

public:
	VertexArrayBuffer(size_t bufferSize, size_t attribOffset);
	VertexArrayBuffer(size_t bufferSize, size_t attribOffset, const void* data);

	void AssignAttribBatchIndices(unsigned int first, unsigned int count);
	void SetData(int offset, int size, const void* data);

	GLuint GetBufferID() const;
	size_t GetSize() const;
	size_t GetInitialOffset() const;
	unsigned int GetFirstAttribBatchIndex() const;
	unsigned int GetAttribBatchIndexCount() const;

	void Delete();
	~VertexArrayBuffer();
};