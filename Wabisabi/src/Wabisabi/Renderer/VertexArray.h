#pragma once
#include "wbpch.h"
#include "Buffer.h"
namespace Wabisabi
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void AddVertexBuffer(const void* data, size_t size,BufferLayout& layout) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const uint32_t* data, uint32_t count) = 0;
		inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
		static VertexArray* Create();
	};
}