#include "wbpch.h"
#include "Mesh.h"
#include "Wabisabi/Loader.h"
namespace Wabisabi
{
	Mesh::Mesh(const std::string& path)
	{
		Loader::LoadObj(path,*this);
	}
	void Mesh::PushPosition(glm::vec3 pos)
	{
		m_Vertex.push_back(pos.x);
		m_Vertex.push_back(pos.y);
		m_Vertex.push_back(pos.z);
	}

	void Mesh::PushTextureCoordinate(glm::vec2 texture)
	{
		m_Vertex.push_back(texture.x);
		m_Vertex.push_back(texture.y);
	}

	void Mesh::Reserve(size_t size)
	{
		m_Vertex.reserve(size);
	}

	void Mesh::PushNormal(glm::vec3 normal)
	{
		m_Vertex.push_back(normal.x);
		m_Vertex.push_back(normal.y);
		m_Vertex.push_back(normal.z);
	}

}
