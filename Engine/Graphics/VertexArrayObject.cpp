#include"VertexArrayObject.h"
#include"Buffer.h"
#include<iostream>

VertexAttribute::VertexAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset):
	index(index), numElements(numElements), dataType(dataType), attribType(attribType), relativeOffset(relativeOffset)
{
}

VertexAttributeBatch::VertexAttributeBatch()
{
}

void VertexAttributeBatch::AddAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset)
{
	attributes.emplace_back(index, numElements, dataType, attribType, relativeOffset);
}

std::vector<VertexAttribute>::const_iterator VertexAttributeBatch::GetIteratorStart() const
{
	return attributes.begin();
}

std::vector<VertexAttribute>::const_iterator VertexAttributeBatch::GetIteratorEnd() const
{
	return attributes.end();
}

VertexArrayObject::VertexArrayObject()
{
	glCreateVertexArrays(1, &vaoID);
}

void VertexArrayObject::StartNewAttribBatch()
{
	batchList.emplace_back();
}

void VertexArrayObject::AddExistingAttribBatch(const VertexAttributeBatch& batch)
{
	batchList.push_back(batch);
}

void VertexArrayObject::AddExistingAttribBatches(const std::vector<VertexAttributeBatch>& batches)
{
	batchList.insert(batchList.end(), batches.begin(), batches.end());
}

void VertexArrayObject::AddAttribToBatch(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset)
{
	batchList.back().AddAttribute(index, numElements, dataType, attribType, relativeOffset);
}

void VertexArrayObject::RegisterArrayBuffer(unsigned int firstBatchIndex, unsigned int indexCount, unsigned int numVertices, size_t attribOffset, Buffer * buffer)
{
	unsigned int finalBatchIndex = firstBatchIndex + indexCount;
	for (unsigned int j = firstBatchIndex; j < finalBatchIndex; j++)
	{
		size_t stride = 0;
		std::vector<VertexAttribute>::const_iterator it = batchList[j].GetIteratorStart();
		for (it; it != batchList[j].GetIteratorEnd(); it++)
		{
			const VertexAttribute& currentAttrib = *it;
			stride += currentAttrib.numElements*SizeOfType(currentAttrib.dataType);
		}
		glVertexArrayVertexBuffer(vaoID, j, buffer->GetBufferID(), attribOffset, stride);
		attribOffset += stride * numVertices; //TODO fix logic to account for instance arrays
	}
}
 
void VertexArrayObject::RegisterElementBuffer(Buffer * buffer) const
{
	glVertexArrayElementBuffer(vaoID, buffer->GetBufferID());
}

void VertexArrayObject::UnregisterBuffers() const
{
	glVertexArrayVertexBuffers(vaoID, 0, batchList.size(), NULL, NULL, NULL);
	glVertexArrayElementBuffer(vaoID, 0);
}

void VertexArrayObject::PrepareAttributes()
{
	int bindingPoint = 0;
	for (std::vector<VertexAttributeBatch>::iterator i = batchList.begin(); i != batchList.end(); i++, bindingPoint++)
	{
		std::vector<VertexAttribute>::const_iterator it = i->GetIteratorStart();
		for (it; it != i->GetIteratorEnd(); it++)
		{
			glEnableVertexArrayAttrib(vaoID, it->index);
			switch (it->attribType)
			{
				case AttribType::FLOAT: glVertexArrayAttribFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->dataType), GL_FALSE, it->relativeOffset); break;
				case AttribType::FLOAT_NORM: glVertexArrayAttribFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->dataType), GL_TRUE, it->relativeOffset); break;
				case AttribType::INT: glVertexArrayAttribIFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->dataType), it->relativeOffset); break;
				case AttribType::DOUBLE: glVertexArrayAttribLFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->dataType), it->relativeOffset); break;
			}
			glVertexArrayAttribBinding(vaoID, it->index, bindingPoint);
		}
	}
}

size_t VertexArrayObject::GetNumberOfBatches() const
{
	return batchList.size();
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(vaoID);
}

void VertexArrayObject::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &vaoID);
}

VertexArrayObject::~VertexArrayObject()
{
	this->Delete();
}

size_t VertexArrayObject::SizeOfType(const DataType & type) const
{
	switch (type)
	{
	case DataType::BYTE: return sizeof(GLbyte);
	case DataType::UBYTE: return sizeof(GLubyte);
	case DataType::SHORT: return sizeof(GLshort);
	case DataType::USHORT:return sizeof(GLushort);
	case DataType::INT: return sizeof(GLint);
	case DataType::UINT: return sizeof(GLuint);
	case DataType::HALF_FLOAT: return sizeof(GLhalf);
	case DataType::FLOAT: return sizeof(GLfloat);
	case DataType::DOUBLE: return sizeof(GLdouble);
	default: return 0;
	}
}

GLenum VertexArrayObject::TypeToOpenGL(DataType type) const
{
	switch (type)
	{
	case DataType::BYTE: return GL_BYTE;
	case DataType::UBYTE: return GL_UNSIGNED_BYTE;
	case DataType::SHORT: return GL_SHORT;
	case DataType::USHORT:return GL_UNSIGNED_SHORT;
	case DataType::INT: return GL_INT;
	case DataType::UINT: return GL_UNSIGNED_INT;
	case DataType::HALF_FLOAT: return GL_HALF_FLOAT;
	case DataType::FLOAT: return GL_FLOAT;
	case DataType::DOUBLE: return GL_DOUBLE;
	default: return GL_INVALID_ENUM;
	}
}
