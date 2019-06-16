#pragma once
#include "wbpch.h"
#include "Wabisabi/Renderer/Buffer.h"

namespace Wabisabi
{
	class OpenglVertexBuffer : public VertexBuffer
	{
	public:
		OpenglVertexBuffer(const void* data, uint32_t size);
		virtual ~OpenglVertexBuffer();
		virtual void Bind() const override final;
		virtual void UnBind() const override final;
		virtual void Reset(const void* data, uint32_t size) const override final;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout= layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
	private:
		BufferLayout m_Layout;
		uint32_t m_RendererId;
	};

	class OpenglIndexBuffer: public IndexBuffer
	{
	public:
		OpenglIndexBuffer(const uint32_t* data, uint32_t count);
		virtual ~OpenglIndexBuffer();
		virtual void Bind() const override final;
		virtual void UnBind() const override final;
		virtual void Reset(const uint32_t* data, uint32_t count) const override final;
		inline virtual uint32_t GetCount() const override final { return m_Count; }
	private:
		uint32_t m_RendererId;
		uint32_t m_Count;
	
	};
}
