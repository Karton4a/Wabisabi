#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Platform/Opengl/OpenglShader.h" //HACK Platform Specific Code
#include "Wabisabi/Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
		void SetRotation(Float angle, Float3 vec);
		void Rotate(Float angle, Float3 vec);
		void SetPosition(Float3 vec);
		void Move(Float3 vec);
		void SetSize(Float3 vec);
		void Scale(Float3 vec);
		const Float4x4& GetModel() const{ return m_Model; }
	private:
		inline void CaclulateModel() { m_Model = m_Translation * m_Rotation * m_Scaling; };
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<Material> m_Materials;
		Float4x4 m_Rotation = Float4x4(1.f);
		Float4x4 m_Translation = Float4x4(1.f);
		Float4x4 m_Scaling = Float4x4(1.f);
		Float4x4 m_Model = Float4x4(1.f);
	};
}