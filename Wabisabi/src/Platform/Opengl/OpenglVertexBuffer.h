#pragma once
#include "wbpch.h"
#include "Wabisabi/Renderer/VertexBuffer.h"
namespace Wabisabi
{
	class OpenglVertexBuffer : public VertexBuffer
	{
	public:
		OpenglVertexBuffer(const void* data, uint32_t size);
		virtual ~OpenglVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void Reset(const void* data, uint32_t size) const override;
	private:
		uint32_t m_RendererId;
	};
}
