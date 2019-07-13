#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Platform/Opengl/OpenglShader.h" //HACK Platform Specific Code
#include "Wabisabi/Types.h"
namespace Wabisabi
{
	class Model
	{
	public:
		Model(const std::string& path);
		inline const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }
		std::vector<Mesh>::iterator begin() { return m_Meshes.begin(); }
		std::vector<Mesh>::iterator end() { return m_Meshes.end(); }
		void BindMaterial(MaterialId id,OpenglShader& shader) const;
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<Material> m_Materials;
	};
}