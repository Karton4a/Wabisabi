#include "wbpch.h"
#include "Model.h"
#include "Wabisabi/Loader.h"
namespace Wabisabi
{
	Model::Model(const std::string& path)
	{
		Loader::LoadObj(path, m_Meshes,m_Materials);
	}
	void Model::BindMaterial(MaterialId id, OpenglShader& shader) const 
	{
		if (id != -1)
		{
			m_Materials.at(id).Bind(shader);
		}
	}
	
}
