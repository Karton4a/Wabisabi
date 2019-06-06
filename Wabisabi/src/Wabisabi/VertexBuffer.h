#pragma once
#include "wbpch.h"
class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint32_t size);
	virtual ~VertexBuffer();
	virtual void Bind() const;
	virtual void UnBind() const;
protected:
	VertexBuffer()
		:m_Instance(nullptr)
	{}
private:
	VertexBuffer* m_Instance;
};