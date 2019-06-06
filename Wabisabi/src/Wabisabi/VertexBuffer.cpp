#include "wbpch.h"
#include "VertexBuffer.h"
#include "OpenglVertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	m_Instance = new OpenglVertexBuffer(data, size);
}

VertexBuffer::~VertexBuffer()
{
	if (m_Instance)
	{
		delete m_Instance;
	}
}

void VertexBuffer::Bind() const
{
	m_Instance->Bind();
}

void VertexBuffer::UnBind() const
{
	m_Instance->UnBind();
}
