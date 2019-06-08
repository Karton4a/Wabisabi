#include "wbpch.h"
#include "VertexBuffer.h"
#include "Platform/Opengl/OpenglVertexBuffer.h"
#include "Renderer.h"
namespace Wabisabi
{
	VertexBuffer::VertexBuffer(const void* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		//TODO решить что с этим делать		
		}
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

	void VertexBuffer::Reset(const void* data, uint32_t size) const
	{
		m_Instance->Reset(data, size);
	}

}
