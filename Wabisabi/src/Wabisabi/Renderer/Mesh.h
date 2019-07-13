#pragma once
#include "VertexArray.h"
#include "Wabisabi/Types.h"
#include <glm/glm.hpp>
namespace Wabisabi
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 Texture;
		glm::vec3 Normals;
	};
	class Mesh
	{
	public:
		std::vector<float_t> Vertex;
		std::vector<uint32_t> Indicies;
	public:
		Mesh() {};
		Mesh(std::vector<glm::vec3>& vertexCoordinates, std::vector<glm::vec2>& textureCoordinates,
			std::vector<glm::vec3>& normalCoordinates, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& textureIndices,
			std::vector<unsigned int>& normalIndices);
		inline void SetName(const std::string name) { m_Name = name; }
		inline const std::string& GetName() { return m_Name; }
		inline const std::unique_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }
		inline void SetMaterialId(MaterialId id) { m_MaterialId = id; }
		inline MaterialId GetMaterialId() { return m_MaterialId; }
	private:
		MaterialId m_MaterialId;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::string m_Name;
	};
}