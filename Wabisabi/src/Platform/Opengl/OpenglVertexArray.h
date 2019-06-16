#pragma once
#include "Wabisabi/Renderer/VertexArray.h"
namespace Wabisabi
{
	class OpenglVertexArray : public VertexArray
	{
	public:
		OpenglVertexArray();
		virtual ~OpenglVertexArray();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer) override;
		virtual void AddVertexBuffer(const void* data,uint32_t size, BufferLayout& layout) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const uint32_t* data, uint32_t count) override;
		inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint8_t m_LayoutLevels;
		uint32_t m_RendererId;
	};
}