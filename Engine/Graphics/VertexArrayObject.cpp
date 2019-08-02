#include"VertexArrayObject.h"
#include"VertexArrayBuffer.h"
#include"../CoreSystems/Math//Vector3.h"
#include<iostream>
/*
VertexArrayObject::VertexArrayObject(): bindingPointCounter(0)
{
	glCreateVertexArrays(1, &vaoID);
}


void VertexArrayObject::AddVertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized)
{
	attribs.emplace(index, numElements, type, offset, normalized);
}

void VertexArrayObject::AddArrayBuffer(VertexArrayBuffer * vertexArrayBuffer)
{
	vboList.push_back(vertexArrayBuffer);
}

void VertexArrayObject::SetArrayBuffers(const std::vector<VertexArrayBuffer*>& arrayBuffers)
{
	vboList = arrayBuffers;
}

void VertexArrayObject::PrepareVertexAttributes()
{
	std::set<VertexAttribute>::iterator i=attribs.begin();
	for (i; i != attribs.end(); i++)
	{
		glEnableVertexArrayAttrib(vaoID, i->index);
		glVertexArrayAttribFormat(vaoID, i->index, i->numElements, TypeToOpenGL(i->type), i->normalized, i->offset);
	}
}

void VertexArrayObject::BindVertexArrays()
{
	for (std::vector<VertexArrayBuffer>::size_type i = 0; i < vboList.size(); i++)
	{
		std::vector<int> attribIndices = vboList[i]->GetAttribIndices();
		if (vboList[i]->InterleavedAttribs())
		{
			size_t stride = 0;
			for (std::vector<int>::size_type j = 0; j < attribIndices.size(); j++)
			{
				std::set<VertexAttribute>::iterator current = attribs.find(VertexAttribute(attribIndices[j]));
				stride += current->numElements * SizeOfType(current->type);
				glVertexArrayAttribBinding(vaoID, attribIndices[j], bindingPointCounter);
			}
			glVertexArrayVertexBuffer(vaoID, bindingPointCounter++, vboList[i]->GetBufferID(), vboList[i]->GetInitialOffset(), stride);
		}
		else
		{
			size_t offset = 0;
			for (std::vector<int>::size_type j = 0; j < attribIndices.size(); j++)
			{	
				std::set<VertexAttribute>::iterator current = attribs.find(VertexAttribute(attribIndices[j]));
				size_t stride = SizeOfType(current->type) * current->numElements;
				glVertexArrayAttribBinding(vaoID, attribIndices[j], bindingPointCounter);
				glVertexArrayVertexBuffer(vaoID, bindingPointCounter, vboList[i]->GetBufferID(), offset, stride);
				bindingPointCounter++;
				offset += vboList[i]->GetNumberOfVertices() * stride;
			}
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


void VertexArrayObject::RemoveArrayBuffers()
{
	vboList.clear();
	bindingPointCounter = 0;
}

void VertexArrayObject::Delete()
{
	for (std::vector<VertexArrayBuffer>::size_type i = 0; i < vboList.size(); i++)
	{
		vboList[i]->Delete();//TODO might be changed in the future!
	}
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

GLenum VertexArrayObject::TypeToOpenGL(const API_Type & type)
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
}*/

VertexAttribute::VertexAttribute(unsigned int index) :index(index), numElements(0), offset(0), normalized(false)
{
}

VertexAttribute::VertexAttribute(unsigned int index, int numElements, API_Type type, size_t offset, bool normalized):
	index(index), numElements(numElements), type(type), offset(offset), normalized(normalized)
{
}

bool VertexAttribute::operator<(const VertexAttribute & attrib) const
{
	return this->index < attrib.index;
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

void VertexArrayObject::AddArrayBuffer(unsigned int firstBatchIndex, unsigned int count, VertexArrayBuffer * buffer)
{
	//TODO check against batchList.size()
	buffer->AssignAttribBatchIndices(firstBatchIndex, count);
	vboList.push_back(buffer);
}

void VertexArrayObject::SetNumberOfVertices(unsigned int numberOfVertices)
{
	numVertices = numberOfVertices;
}

void VertexArrayObject::PrepareAttributes()
{
	for (std::vector<VertexAttributeBatch*>::iterator i = batchList.begin(); i != batchList.end(); i++)
	{
		std::vector<VertexAttribute>& currentBatch = (*i)->attributes;
		std::vector<VertexAttribute>::iterator it = currentBatch.begin();
		for (it; it != currentBatch.end(); it++)
		{
			glEnableVertexArrayAttrib(vaoID, it->index);
			glVertexArrayAttribFormat(vaoID, it->index, it->numElements, TypeToOpenGL(it->type), it->normalized, it->offset);
		}
	}
}

void VertexArrayObject::RegisterBuffers()
{
	for (std::vector<VertexArrayBuffer*>::iterator i = vboList.begin(); i != vboList.end(); i++)
	{
		const VertexArrayBuffer* currentVBO = *i;
		size_t offset = currentVBO->GetInitialOffset();
		unsigned int firstIndex = currentVBO->GetFirstAttribBatchIndex();
		unsigned int lastIndex = firstIndex + currentVBO->GetAttribBatchIndexCount();
		for (unsigned int j = firstIndex; j < lastIndex; j++)
		{
			//TODO attributes.size==0 --- error
			if (batchList[j]->attributes.size() == 1) //Separate Attributes!
			{
				VertexAttribute* currentAttrib = &(batchList[j]->attributes[0]);
				size_t stride = currentAttrib->numElements*SizeOfType(currentAttrib->type);
				glVertexArrayAttribBinding(vaoID, currentAttrib->index, j);
				glVertexArrayVertexBuffer(vaoID, j, currentVBO->GetBufferID(), offset, stride);
				offset += stride * numVertices;
			}
			if (batchList[j]->attributes.size() > 1) //Interleaved Attributes!
			{
				size_t stride = 0;
				std::vector<VertexAttribute>::iterator it = batchList[j]->attributes.begin();
				for (it; it != batchList[j]->attributes.end(); it++)
				{
					VertexAttribute& currentAttrib = *it;
					stride += currentAttrib.numElements*SizeOfType(currentAttrib.type);
					glVertexArrayAttribBinding(vaoID, currentAttrib.index, j);
				}
				glVertexArrayVertexBuffer(vaoID, j, currentVBO->GetBufferID(), offset, stride);
				offset += stride * numVertices;
			}
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
	for (std::vector<VertexArrayBuffer>::size_type i = 0; i < vboList.size(); i++)
	{
		vboList[i]->Delete();//TODO might be changed in the future!
	}
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
