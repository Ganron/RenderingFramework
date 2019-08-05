#include"Buffer.h"

Buffer::Buffer(size_t bufferSize) :size(bufferSize)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
}

Buffer::Buffer(size_t bufferSize, const void * data) :size(bufferSize)
{
	glCreateBuffers(1, &bufferID);
	glNamedBufferStorage(bufferID, size, data, GL_DYNAMIC_STORAGE_BIT);
}


void Buffer::SetData(int offset, int size, const void * data)
{
	glNamedBufferSubData(bufferID, offset, size, data);
}

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
}
