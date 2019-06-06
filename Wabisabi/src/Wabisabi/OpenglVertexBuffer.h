#pragma once
#include "wbpch.h"
#include "VertexBuffer.h"

class OpenglVertexBuffer : public VertexBuffer
{
public:
	OpenglVertexBuffer(const void* data, uint32_t size);
	virtual void Bind() const override;
	virtual void UnBind() const override;
private:
	uint32_t m_RendererId;
};