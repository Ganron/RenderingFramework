#include"Buffer.h"

Buffer::Buffer(): bufferID(0), size(0), maxOffset(0)
{
}

Buffer::Buffer(size_t bufferSize) : bufferID(0), size(bufferSize), maxOffset(0)
{
	Init(bufferSize);
}

Buffer::Buffer(size_t bufferSize, const void * data) : bufferID(0), size(bufferSize), maxOffset(bufferSize)
{
	Init(bufferSize, data);
}

void Buffer::Init(size_t bufferSize)
{
	if (size != 0)
	{
		glCreateBuffers(1, &bufferID);
		glNamedBufferStorage(bufferID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
	}
}

void Buffer::Init(size_t bufferSize, const void * data)
{
	if (size != 0)
	{
		glCreateBuffers(1, &bufferID);
		glNamedBufferStorage(bufferID, size, data, GL_DYNAMIC_STORAGE_BIT);
	}
}

void Buffer::SetData(size_t offset, size_t size, const void * data)
{
	if (maxOffset < offset + size)
	{
		maxOffset = offset + size;
	}
	glNamedBufferSubData(bufferID, offset, size, data);
}

void Buffer::BindUniform(unsigned int index, size_t offset, size_t size) const
{
	glBindBufferRange(GL_UNIFORM_BUFFER, index, bufferID, offset, size);
}

void Buffer::BindShaderStorage(unsigned int index, size_t offset, size_t size) const
{
	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, index, bufferID, offset, size);
}
/*
void Buffer::BindTransformFeedback(unsigned int index, size_t offset, size_t size) const
{
	glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, index, bufferID, offset, size);
}

void Buffer::BindAtomicCounter(unsigned int index, size_t offset, size_t size) const
{
	glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, index, bufferID, offset, size);
}
*/
GLuint Buffer::GetBufferID() const
{
	return bufferID;
}

size_t Buffer::GetSize() const
{
	return size;
}

size_t Buffer::GetMaxOffset() const
{
	return maxOffset;
}

void Buffer::Delete()
{
	glDeleteBuffers(1, &bufferID);
}

Buffer::~Buffer()
{
}
