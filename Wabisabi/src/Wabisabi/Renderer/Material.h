#pragma once
#include "Texture.h"
#include "Platform/Opengl/OpenglShader.h"
#include <array>
namespace Wabisabi
{
	class Material
	{
	public:
		Material(Texture* diffuse, Texture* specular, int32_t shiness);
		void Bind(OpenglShader& shader) const;
		void SetDiffuseTexture(Texture* diffuse);
		void SetSpecularTexture(Texture* specular);
	private:
		std::unordered_map<std::string, int32_t> m_Uniforms;
		std::array<std::shared_ptr<Texture>, 2> m_Textures;
	};
}
