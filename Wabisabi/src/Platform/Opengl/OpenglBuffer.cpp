#include "wbpch.h"
#include "OpenglBuffer.h"
#include <glad/glad.h>
namespace Wabisabi
{
	
	OpenglVertexBuffer::OpenglVertexBuffer(const void* data, uint32_t size) 
		: m_RendererId(0)
	{
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenglVertexBuffer::~OpenglVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenglVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void OpenglVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenglVertexBuffer::Reset(const void* data, uint32_t size) const
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		
	}

	OpenglIndexBuffer::OpenglIndexBuffer(const uint32_t* data, uint32_t count)
		:m_RendererId(0) , m_Count(count)
	{
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}

	OpenglIndexBuffer::~OpenglIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenglIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void OpenglIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenglIndexBuffer::Reset(const uint32_t* data, uint32_t count) const
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
		
	}

}