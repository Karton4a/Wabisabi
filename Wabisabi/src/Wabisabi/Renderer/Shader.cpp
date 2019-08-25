#include "wbpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Wabisabi/Log.h"
#include "Platform/Opengl/OpenglShader.h"
namespace Wabisabi
{
	Ref<Shader> Shader::Create(const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: WB_CORE_ASSERT(false, "None API doesn't supported") return nullptr;
		case RendererAPI::OpenGL: return std::make_shared<OpenglShader>(vertexsrc, fragmentsrc);
		default: WB_CORE_ASSERT(false, "API doesn't supported"); return nullptr;
		}
	}
}
