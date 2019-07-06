#pragma once
#include "Texture.h"
#include "Platform/Opengl/OpenglShader.h"

namespace Wabisabi
{
	using Color = glm::vec4;
	using Type = uint8_t;
	
	class Material
	{
	public:
		enum MaterialType
		{
			None = 0,
			ColorBased = 1 << 0,
			diffuseMapping = 1 << 1,
			SpecularMapping = 1 << 2,
			NormalMapping = 1 << 3,
		};
	public:
		Material(Texture* diffuse, Texture* specular = nullptr, float_t shiness = 32.f, Texture* normal = nullptr);
		Material(const Color& diffuse, const Color& specular, float_t shiness , const Color& ambient = Color(-1.f));
		void Bind(OpenglShader& shader) const;
		inline bool HasParam(MaterialType type) const { return (m_Type & type); };
	private:
		std::shared_ptr<Texture> m_Diffuse;
		std::shared_ptr<Texture> m_Specular;
		std::shared_ptr<Texture> m_Normals;
		float_t m_Shiness;
		Color m_AmbientColor;
		Color m_DiffuseColor;
		Color m_SpecularColor;
		Type m_Type = None;
	};
}
