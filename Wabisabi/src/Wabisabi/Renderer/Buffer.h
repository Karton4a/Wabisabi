#pragma once
#include "wbpch.h"
namespace Wabisabi
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Reset(const void* data, uint32_t size) const = 0;
		static VertexBuffer* Create(const void* data,uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		inline virtual uint32_t GetCount() const = 0;
		virtual void Reset(const uint32_t* data, uint32_t count) const = 0;
		static IndexBuffer* Create(const uint32_t* data, uint32_t count);

	};
}
