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
	void Model::SetRotation(Float angle, Float3 vec) 
	{ 
		m_Rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), vec); 
		CaclulateModel();
	}
	void Model::Rotate(Float angle, Float3 vec) 
	{ 
		m_Rotation = glm::rotate(m_Rotation, glm::radians(angle), vec);
		CaclulateModel();
	}
	void Model::SetPosition(Float3 vec) 
	{ 
		m_Translation = glm::translate(glm::mat4(1.f), vec);
		CaclulateModel();
	}
	void Model::Move(Float3 vec) 
	{ 
		m_Translation = glm::translate(m_Translation, vec);
		CaclulateModel();
	}
	void Model::SetSize(Float3 vec) 
	{ 
		m_Scaling = glm::scale(glm::mat4(1.f), vec); 
		CaclulateModel();
	}
	void Model::Scale(Float3 vec) 
	{ 
		m_Scaling = glm::scale(m_Scaling, vec);
		CaclulateModel();
	}
	
}
