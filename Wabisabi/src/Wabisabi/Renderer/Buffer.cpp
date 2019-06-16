#include "wbpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Wabisabi/Log.h"
#include "Platform/Opengl/OpenglBuffer.h"
namespace Wabisabi
{
	VertexBuffer* VertexBuffer::Create(const void* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				WB_CORE_ASSERT(false, "None API doesn't supported") return nullptr;
			case RendererAPI::OpenGL: return new OpenglVertexBuffer(data, size);
		}
		WB_CORE_ASSERT(false, "None API is passed")
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(const uint32_t* data, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				WB_CORE_ASSERT(false, "None API doesn't supported") return nullptr;
			case RendererAPI::OpenGL: return new OpenglIndexBuffer(data, count);
		}
		WB_CORE_ASSERT(false, "None API is passed")
		return nullptr;
	}
}