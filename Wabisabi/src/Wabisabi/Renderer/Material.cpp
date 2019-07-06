#include "wbpch.h"
#include "Material.h"
namespace Wabisabi
{
	Material::Material(Texture* diffuse, Texture* specular, float_t shiness, Texture* normal)
	{
		if (normal != nullptr)
		{
			m_Type |= NormalMapping;
			m_Normals.reset(normal);
		}
		if (specular != nullptr)
		{
			m_Type |= SpecularMapping;
			m_Specular.reset(specular);
		}
		m_Diffuse.reset(diffuse);
		m_Type |= diffuseMapping;
		m_Shiness = shiness;

	}
	Material::Material(const Color& diffuse, const Color& specular, float_t shiness, const Color& ambient)
		:m_DiffuseColor(diffuse),m_SpecularColor(specular),m_Shiness(shiness)
	{
		if (ambient != Color(-1.f))
			m_AmbientColor = ambient;
		else
			m_AmbientColor = diffuse;
		m_Type = ColorBased;
	}
	void Material::Bind(OpenglShader& shader) const
	{
		if (this->HasParam(diffuseMapping))
		{
			m_Diffuse->Bind(0);
			shader.SetUniform("material.diffuse", 0);
			if (this->HasParam(SpecularMapping))
			{
				m_Specular->Bind(1);
				shader.SetUniform("material.specular", 1);

				shader.SetUniform("material.shiness", m_Shiness);
			}
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
