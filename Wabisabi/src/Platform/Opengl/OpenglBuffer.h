#pragma once
#include "wbpch.h"
#include "Wabisabi/Renderer/Buffer.h"
#include "Wabisabi/Types.h"

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
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout= layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
	private:
		BufferLayout m_Layout;
		RendererId m_RendererId;
	};

	class OpenglIndexBuffer final : public IndexBuffer
	{
	public:
		OpenglIndexBuffer(const uint32_t* data, uint32_t count);
		virtual ~OpenglIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void Reset(const uint32_t* data, uint32_t count) const override;
		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		RendererId m_RendererId;
		uint32_t m_Count;
	
	};
}
