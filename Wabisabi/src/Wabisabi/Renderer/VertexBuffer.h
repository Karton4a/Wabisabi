#pragma once
#include "wbpch.h"


namespace Wabisabi
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint32_t size);
		virtual ~VertexBuffer();
		virtual void Bind() const;
		virtual void UnBind() const;
		virtual void Reset(const void* data, uint32_t size) const;
	protected:
		VertexBuffer()
			:m_Instance(nullptr)
		{}
	private:
		VertexBuffer* m_Instance;
	};
}
