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

	bool SetData(size_t offset, size_t dataSize, const void* data);

	void BindUniform(unsigned int index, size_t offset, size_t size) const;
	void BindShaderStorage(unsigned int index, size_t offset, size_t size) const;
	//void BindTransformFeedback(unsigned int index, size_t offset, size_t size) const;
	//void BindAtomicCounter(unsigned int index, size_t offset, size_t size) const;
	//TODO Memory barriers

	GLuint GetBufferID() const;
	size_t GetSize() const;

	void Delete();
	~Buffer();
};