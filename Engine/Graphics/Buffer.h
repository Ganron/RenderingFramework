#pragma once
#include<glad/glad.h>

class Buffer 
{
private:
	GLuint bufferID;
	size_t size;

public:
	Buffer(size_t bufferSize);
	Buffer(size_t bufferSize, const void* data);

	void SetData(size_t offset, size_t size, const void* data);

	void BindUniform(unsigned int index, size_t offset, size_t size);
	void BindShaderStorage(unsigned int index, size_t offset, size_t size);
	void BindTransformFeedback(unsigned int index, size_t offset, size_t size);
	void BindAtomicCounter(unsigned int index, size_t offset, size_t size);

	GLuint GetBufferID() const;
	size_t GetSize() const;

	void Delete();
	~Buffer();
};