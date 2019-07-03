#include "wbpch.h"
#include "Material.h"
namespace Wabisabi
{
	Material::Material(Texture* diffuse, Texture* specular, int32_t shiness, Texture* normal)
	{
		if (normal == nullptr)
		{
			m_Type = TextureMapping;
		}
		else
		{
			m_Type = TextureMapping | NormalMapping;
			m_Normals.reset(normal);
		}
		m_Diffuse.reset(diffuse);
		m_Specular.reset(specular);
		m_Shiness = shiness;
	}
	Material::Material(const Color& diffuse, const Color& specular, int32_t shiness, const Color& ambient)
		:m_DiffuseColor(diffuse),m_SpecularColor(specular),m_Shiness(shiness)
	{
		if (ambient != Color(-1.f))
			m_AmbientColor = ambient;
		else
			m_AmbientColor = diffuse;
	}
	void Material::Bind(OpenglShader& shader) const
	{
		if (this->HasParam(TextureMapping))
		{
			m_Diffuse->Bind(0);
			shader.SetUniform("material.diffuse", 0);

			m_Specular->Bind(1);
			shader.SetUniform("material.specular", 1);

			shader.SetUniform("material.shiness", m_Shiness);

			if (this->HasParam(NormalMapping))
			{
				m_Normals->Bind(2);
				shader.SetUniform("material.normal", 2);
			}
		}
		else if (this->HasParam(ColorBased))
		{
			shader.SetUniform("material.ambient", m_AmbientColor.r, m_AmbientColor.g, m_AmbientColor.b);
			shader.SetUniform("material.diffuse", m_DiffuseColor.r, m_DiffuseColor.g, m_DiffuseColor.b);
			shader.SetUniform("material.specular", m_SpecularColor.r, m_SpecularColor.g, m_SpecularColor.b);
			shader.SetUniform("material.shiness", m_Shiness);
		}
	}

}
