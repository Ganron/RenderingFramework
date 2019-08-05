#include"VertexArrayObject.h"
#include"Buffer.h"

VertexAttribute::VertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized):
	index(index), numElements(numElements), type(type), offset(offset), normalized(normalized)
{
}

void VertexAttributeBatch::AddAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized)
{
	attributes.emplace_back(index, numElements, type, offset, normalized);
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
			stride += currentAttrib.numElements*SizeOfType(currentAttrib.type);
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
			glVertexArrayAttribFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->type), it->normalized, it->offset);
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

size_t VertexArrayObject::SizeOfType(const API_Type & type) const
{
	switch (type)
	{
	case API_Type::BYTE: return sizeof(GLbyte);
	case API_Type::U_BYTE: return sizeof(GLubyte);
	case API_Type::SHORT: return sizeof(GLshort);
	case API_Type::U_SHORT:return sizeof(GLushort);
	case API_Type::INT: return sizeof(GLint);
	case API_Type::U_INT: return sizeof(GLuint);
	case API_Type::HALF_FLOAT: return sizeof(GLhalf);
	case API_Type::FLOAT: return sizeof(GLfloat);
	case API_Type::DOUBLE: return sizeof(GLdouble);
	default: return 0;
	}
}

GLenum VertexArrayObject::TypeToOpenGL(API_Type type) const
{
	switch (type)
	{
	case API_Type::BYTE: return GL_BYTE;
	case API_Type::U_BYTE: return GL_UNSIGNED_BYTE;
	case API_Type::SHORT: return GL_SHORT;
	case API_Type::U_SHORT:return GL_UNSIGNED_SHORT;
	case API_Type::INT: return GL_INT;
	case API_Type::U_INT: return GL_UNSIGNED_INT;
	case API_Type::HALF_FLOAT: return GL_HALF_FLOAT;
	case API_Type::FLOAT: return GL_FLOAT;
	case API_Type::DOUBLE: return GL_DOUBLE;
	default: return GL_INVALID_ENUM;
	}
}
