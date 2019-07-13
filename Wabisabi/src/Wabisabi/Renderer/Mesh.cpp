#include "wbpch.h"
#include "Mesh.h"
#include "Buffer.h"
namespace Wabisabi
{
	Mesh::Mesh(std::vector<glm::vec3>& vertexCoordinates, std::vector<glm::vec2>& textureCoordinates,
		std::vector<glm::vec3>& normalCoordinates, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& textureIndices,
		std::vector<unsigned int>& normalIndices) : m_MaterialId(-1)
	{
	
		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout({ {ShaderDataType::Float3,"position"} });

		if (!textureIndices.empty())
			layout += {ShaderDataType::Float2, "texture"};
		if (!normalIndices.empty())
			layout += {ShaderDataType::Float3, "normals"};

		uint8_t offset = layout.GetStride() / sizeof(float);

		float* vertex = new float[offset];
		uint8_t localOffset = 0;

		for (size_t i = 0; i < vertexIndices.size(); i++)
		{
			glm::vec3 vertexCoord = vertexCoordinates[vertexIndices[i]];
			localOffset = 3;
			memcpy_s(vertex, offset * sizeof(float), &vertexCoord, 3 * sizeof(float));
			if (!textureIndices.empty())
			{
				glm::vec2 textureCoord = textureCoordinates[textureIndices[i]];
				memcpy_s(vertex + localOffset, (offset - localOffset) * sizeof(float), &textureCoord, 2 * sizeof(float));
				localOffset += 2;
			}
			if (!normalIndices.empty())
			{
				glm::vec3 normalCoord = normalCoordinates[normalIndices[i]];
				memcpy_s(vertex + localOffset, (offset - localOffset) * sizeof(float), &normalCoord, 3 * sizeof(float));
				localOffset += 3;
			}

			bool isFinded = false;
			for (size_t j = 0; j < Vertex.size(); j += offset)
			{
				if (memcmp(vertex, &Vertex[j], offset * sizeof(float)) == 0)
				{
					Indicies.push_back(j / offset);
					isFinded = true;
					break;
				}
			}
			if (!isFinded)
			{
				for (size_t j = 0; j < offset; j++)
				{
					Vertex.push_back(vertex[j]);
				}
				Indicies.push_back(Vertex.size()/offset - 1);
			}
		
		}

		m_VertexArray->AddVertexBuffer(&Vertex[0], Vertex.size() * sizeof(float),layout);
		m_VertexArray->SetIndexBuffer(&Indicies[0], Indicies.size());
	}
	

}
