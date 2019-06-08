#include "wbpch.h"
#include "OpenglVertexBuffer.h"
#include <glad/glad.h>
namespace Wabisabi
{
	OpenglVertexBuffer::OpenglVertexBuffer(const void* data, uint32_t size) : m_RendererId(0)
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
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

}