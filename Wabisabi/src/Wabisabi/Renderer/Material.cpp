#include "wbpch.h"
#include "Material.h"
namespace Wabisabi
{
	Material::Material(Texture* diffuse, Texture* specular, int32_t shiness)
	{
		m_Uniforms["material.diffuse"] = 0;
		m_Uniforms["material.specular"] = 1;
		m_Uniforms["material.shiness"] = shiness;
		m_Textures[0].reset(diffuse);
		m_Textures[1].reset(specular);
	}
	void Material::Bind(OpenglShader& shader) const
	{
		int i = 0;
		for (auto& el : m_Uniforms)
		{
			if (i < m_Textures.size())
			{
				m_Textures[i]->Bind(el.second);
			}
			shader.SetUniform(el.first,el.second);
			i++;
		}
	}
	void Material::SetDiffuseTexture(Texture* diffuse)
	{
		m_Textures[0].reset(diffuse);
	}
	void Material::SetSpecularTexture(Texture* specular)
	{
		m_Textures[1].reset(specular);
	}
}
