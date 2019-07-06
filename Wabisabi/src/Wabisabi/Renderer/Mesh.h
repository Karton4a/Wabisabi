#pragma once
#include "VertexArray.h"
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
		Mesh(const std::string& path);
		inline const std::unique_ptr<VertexArray>& GetVertexArray() { return m_VertexArray; }
	private:
		std::unique_ptr<VertexArray> m_VertexArray;
	};
}