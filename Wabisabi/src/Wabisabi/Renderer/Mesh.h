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
		Mesh() {};
		Mesh(const std::string& path);
		void PushPosition(glm::vec3 pos);
		void PushTextureCoordinate(glm::vec2 texture);
		void Reserve(size_t size);
		void PushNormal(glm::vec3 normal);
	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		std::vector<float_t> m_Vertex;
		std::vector<uint32_t> m_Indicies;
	};
}