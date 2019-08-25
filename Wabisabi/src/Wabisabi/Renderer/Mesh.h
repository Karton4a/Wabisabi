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
#pragma region Box
	/*union Box
	{
		Box(Box&& rhs) noexcept
			:Vertices(rhs.Vertices) {}
		Box() = default;
		struct
		{
			struct Square
			{
				glm::vec3 TopLeft;
				glm::vec3 TopRight;
				glm::vec3 BottomRight;
				glm::vec3 BottomLeft;

			};
			Square Top;
			Square Bottom;
		};
		struct
		{
			std::array<glm::vec3, 8> Vertices;
		};
	};*/
#pragma endregion

	class Mesh
	{
	public:
		std::vector<float_t> Vertex;
		std::vector<uint32_t> Indicies;
	public:
		Mesh() = default;
		Mesh(std::vector<glm::vec3>& vertexCoordinates, std::vector<glm::vec2>& textureCoordinates,
			std::vector<glm::vec3>& normalCoordinates, std::vector<int>& vertexIndices, std::vector<int>& textureIndices,
			std::vector<int>& normalIndices);
		inline void SetName(const std::string name) { m_Name = name; }
		inline const std::string& GetName() { return m_Name; }
		inline const std::unique_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }
		inline void SetMaterialId(MaterialId id) { m_MaterialId = id; }
		inline MaterialId GetMaterialId() { return m_MaterialId; }
	private:
		MaterialId m_MaterialId = -1;
		std::unique_ptr<VertexArray> m_VertexArray = nullptr;
		std::string m_Name = "";
	};
}