#include"Buffer.h"
#include<iostream>

Buffer::Buffer(size_t bufferSize) : bufferID(0), size(bufferSize)
{
	if (size != 0)
	{
		glCreateBuffers(1, &bufferID);
		glNamedBufferStorage(bufferID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
	}
}

Buffer::Buffer(size_t bufferSize, const void * data) : bufferID(0), size(bufferSize)
{
	if (size != 0)
	{
		glCreateBuffers(1, &bufferID);
		glNamedBufferStorage(bufferID, size, data, GL_DYNAMIC_STORAGE_BIT);
	}
}


bool Buffer::SetData(size_t offset, size_t dataSize, const void * data)
{
	if (offset + dataSize <= size)
	{
		glNamedBufferSubData(bufferID, offset, dataSize, data);
		return true;
	}
	return false;
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

void Buffer::Delete()
{
	glDeleteBuffers(1, &bufferID);
}

Buffer::~Buffer()
{
	this->Delete();
}
