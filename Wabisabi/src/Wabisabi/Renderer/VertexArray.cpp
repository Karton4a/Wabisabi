#include "wbpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Wabisabi/Log.h"
#include "Platform/Opengl/OpenglVertexArray.h"

namespace Wabisabi
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			WB_CORE_ASSERT(false, "None API doesn't supported") return nullptr;
		case RendererAPI::OpenGL: return new OpenglVertexArray(); 
		}
		WB_CORE_ASSERT(false, "API doesn't supported")
		return nullptr;
	}
}