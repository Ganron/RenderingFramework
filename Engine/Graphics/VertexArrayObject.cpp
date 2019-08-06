#include"VertexArrayObject.h"
#include"Buffer.h"
#include<iostream>

VertexAttribute::VertexAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset):
	index(index), numElements(numElements), dataType(dataType), attribType(attribType), relativeOffset(relativeOffset)
{
}

void VertexAttributeBatch::AddAttribute(unsigned int index, int numElements, DataType dataType, AttribType attribType, size_t relativeOffset)
{
	attributes.emplace_back(index, numElements, dataType, attribType, relativeOffset);
}

VertexArrayObject::VertexArrayObject(unsigned int numberOfVertices) :numVertices(numberOfVertices)
{
	glCreateVertexArrays(1, &vaoID);
}

void VertexArrayObject::AddAttributeBatch(VertexAttributeBatch * batch)
{
	batchList.push_back(batch);
}

void VertexArrayObject::RegisterBuffer(unsigned int firstBatchIndex, unsigned int indexCount, size_t attribOffset, Buffer * buffer)
{
	unsigned int finalBatchIndex = firstBatchIndex + indexCount;
	for (unsigned int j = firstBatchIndex; j < finalBatchIndex; j++)
	{
		size_t stride = 0;
		std::vector<VertexAttribute>::iterator it = batchList[j]->attributes.begin();
		for (it; it != batchList[j]->attributes.end(); it++)
		{
			VertexAttribute& currentAttrib = *it;
			stride += currentAttrib.numElements*SizeOfType(currentAttrib.dataType);
		}
		glVertexArrayVertexBuffer(vaoID, j, buffer->GetBufferID(), attribOffset, stride);
		attribOffset += stride * numVertices;
	}
}

void VertexArrayObject::SetNumberOfVertices(unsigned int numberOfVertices)
{
	numVertices = numberOfVertices;
}

void VertexArrayObject::PrepareAttributes()
{
	int bindingPoint = 0;
	for (std::vector<VertexAttributeBatch*>::iterator i = batchList.begin(); i != batchList.end(); i++, bindingPoint++)
	{
		std::vector<VertexAttribute>& currentBatch = (*i)->attributes;
		std::vector<VertexAttribute>::iterator it = currentBatch.begin();
		for (it; it != currentBatch.end(); it++)
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

void VertexArrayObject::Bind()
{
	glBindVertexArray(vaoID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &vaoID);
}

VertexArrayObject::~VertexArrayObject()
{
}

size_t VertexArrayObject::SizeOfType(const DataType & type) const
{
	switch (type)
	{
	case DataType::BYTE: return sizeof(GLbyte);
	case DataType::U_BYTE: return sizeof(GLubyte);
	case DataType::SHORT: return sizeof(GLshort);
	case DataType::U_SHORT:return sizeof(GLushort);
	case DataType::INT: return sizeof(GLint);
	case DataType::U_INT: return sizeof(GLuint);
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
	case DataType::U_BYTE: return GL_UNSIGNED_BYTE;
	case DataType::SHORT: return GL_SHORT;
	case DataType::U_SHORT:return GL_UNSIGNED_SHORT;
	case DataType::INT: return GL_INT;
	case DataType::U_INT: return GL_UNSIGNED_INT;
	case DataType::HALF_FLOAT: return GL_HALF_FLOAT;
	case DataType::FLOAT: return GL_FLOAT;
	case DataType::DOUBLE: return GL_DOUBLE;
	default: return GL_INVALID_ENUM;
	}
}
