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

	void SetData(int offset, int size, const void* data);

	GLuint GetBufferID() const;
	size_t GetSize() const;

	void Delete();
	~Buffer();
};