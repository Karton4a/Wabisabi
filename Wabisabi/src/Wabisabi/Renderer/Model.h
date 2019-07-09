#pragma once
#include "Mesh.h"
namespace Wabisabi
{
	class Model
	{
	public:
		Model(const std::string& path);
		inline std::vector<Mesh>& GetMeshes() { return m_Meshes; }
		std::vector<Mesh>::iterator begin() { return m_Meshes.begin(); }
		std::vector<Mesh>::iterator end() { return m_Meshes.end(); }
	private:
		std::vector<Mesh> m_Meshes;
	};
}