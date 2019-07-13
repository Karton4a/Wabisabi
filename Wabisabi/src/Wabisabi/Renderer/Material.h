#pragma once
#include "Texture.h"
#include "Platform/Opengl/OpenglShader.h" //HACK Platform Specific Code
#include "Wabisabi/Types.h"
namespace Wabisabi
{
	using RGBA = glm::vec4;
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
		Material() {};
		Material(Texture* diffuse, Texture* specular = nullptr, float_t shiness = 32.f, Texture* normal = nullptr);
		Material(const RGBA& diffuse, const RGBA& specular, float_t shiness , const RGBA& ambient = RGBA(-1.f));
		void Bind(OpenglShader& shader) const;
		inline bool HasParam(MaterialType type) const { return (m_Type & type); };
		inline void SetName(const std::string& name) { m_Name = name; }
		inline const std::string& GetName() { return m_Name; }
	private:
		std::string m_Name;
		std::shared_ptr<Texture> m_Diffuse;
		std::shared_ptr<Texture> m_Specular;
		std::shared_ptr<Texture> m_Normals;
		float_t m_Shiness;
		RGBA m_AmbientColor;
		RGBA m_DiffuseColor;
		RGBA m_SpecularColor;
		Type m_Type = None;
	};
}
