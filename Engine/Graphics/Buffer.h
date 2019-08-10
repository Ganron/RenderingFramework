#pragma once
#include<glad/glad.h>

class Buffer 
{
private:
	GLuint bufferID;
	size_t size;
	size_t maxOffset;

public:
	Buffer();
	Buffer(size_t bufferSize);
	Buffer(size_t bufferSize, const void* data);

	void Init(size_t bufferSize);
	void Init(size_t bufferSize, const void* data);

	void SetData(size_t offset, size_t size, const void* data);

	void BindUniform(unsigned int index, size_t offset, size_t size) const;
	void BindShaderStorage(unsigned int index, size_t offset, size_t size) const;
	void BindTransformFeedback(unsigned int index, size_t offset, size_t size) const;
	void BindAtomicCounter(unsigned int index, size_t offset, size_t size) const;
	//TODO Memory barriers

	GLuint GetBufferID() const;
	size_t GetSize() const;
	size_t GetMaxOffset() const;

	void Delete();
	~Buffer();
};