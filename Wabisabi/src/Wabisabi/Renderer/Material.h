#pragma once
#include "Texture.h"
#include "Platform/Opengl/OpenglShader.h" //TODO Platform Specific Code
#include "Wabisabi/Types.h"
namespace Wabisabi
{
	using RGBA = glm::vec4;
	
	class Material
	{
	public:
		using Type = uint8_t;
		enum MaterialType
		{
			None = 0,
			ColorBased = 1 << 0,
			diffuseMapping = 1 << 1,
			SpecularMapping = 1 << 2,
			NormalMapping = 1 << 3,
		};
	public:
		Material() = default;
		Material(const std::shared_ptr<Texture>& diffuse, const std::shared_ptr<Texture>& specular = std::shared_ptr<Texture>(nullptr), float_t shiness = 32.f, const std::shared_ptr<Texture>& normal = std::shared_ptr<Texture>(nullptr));
		Material(const RGBA& diffuse, const RGBA& specular, float_t shiness , const RGBA& ambient = RGBA(-1.f));
		void Bind(OpenglShader& shader) const;
		inline bool HasParam(MaterialType type) const { return (m_Type & type); };
		inline void SetName(const std::string& name) { m_Name = name; }
		inline const std::string& GetName() { return m_Name; }
	private:
		std::string m_Name = "";
		std::shared_ptr<Texture> m_Diffuse = nullptr;
		std::shared_ptr<Texture> m_Specular = nullptr;
		std::shared_ptr<Texture> m_Normals = nullptr;
		float_t m_Shiness = 0.f;
		RGBA m_AmbientColor = RGBA(0.f);
		RGBA m_DiffuseColor = RGBA(0.f);
		RGBA m_SpecularColor = RGBA(0.f);
		Type m_Type = None;
	};
}
