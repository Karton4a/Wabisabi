#pragma once
#include "wbpch.h"
#include "Wabisabi/Renderer/Texture.h"
#include "Wabisabi/Types.h"
namespace Wabisabi
{
	class OpenglTexture : public Texture
	{
	public:
		OpenglTexture(const std::string& path);
		virtual ~OpenglTexture();
		virtual void Bind(uint8_t slot = 0) const override;
		virtual void UnBind() const override;
	private:
		RendererId m_RendererId;
	};
}