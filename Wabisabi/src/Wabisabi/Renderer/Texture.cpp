#include "wbpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Wabisabi/Log.h"
#include "stb/stb_image.h"
#include "Platform/Opengl/OpenglTexture.h"
namespace Wabisabi
{
	void Texture::LoadTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		m_Data = (uint8_t*)stbi_load(path.c_str(), (int*)&m_Width, (int*)&m_Height, (int*)&m_BPP, 4);
	}
	void Texture::DeleteData()
	{
		if (m_Data) stbi_image_free(m_Data);
	}
	Texture* Texture::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    WB_CORE_ASSERT(false, "None API doesn't supported") return nullptr;
			case RendererAPI::OpenGL:  return new OpenglTexture(path);
		}
		WB_CORE_ASSERT(false, "None API is passed")
		return nullptr;
	}
}