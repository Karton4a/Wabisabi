#include "wbpch.h"
#include "ShaderManager.h"
#include "Platform/Opengl/OpenglShaderManager.h"
#include "Renderer.h"
namespace Wabisabi
{
	int ShaderManager::s_DefaultShaderVersion = 0;
	ShaderManager* ShaderManager::s_Instance = nullptr;
	void ShaderManager::Create()
	{
		if (s_Instance == nullptr)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::None:    
				WB_CORE_ASSERT(false, "None API doesn't supported") 
				s_DefaultShaderVersion = 0;
				s_Instance = nullptr;
				break;
			case RendererAPI::OpenGL:  
				s_DefaultShaderVersion = 330;
				s_Instance = new OpenglShaderManager();
				break;
			default:
				WB_CORE_ASSERT(false, "Unknown API");
				s_DefaultShaderVersion = 0;
				s_Instance = nullptr;
			}
			//WB_CORE_ASSERT(false, "Unknown API");
		}
	}
	void ShaderManager::Delete()
	{
		if (s_Instance != nullptr)
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}
