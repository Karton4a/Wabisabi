#include "wbpch.h"
#include "Mesh.h"
#include "Wabisabi/Loader.h"
#include "Buffer.h"
#ifdef WB_DEBUG
#include <chrono>
#endif // !WB_DEBUG

namespace Wabisabi
{
	Mesh::Mesh(const std::string& path)
	{
		WB_CORE_TIMER_INIT();
	
		m_VertexArray.reset(VertexArray::Create());
		std::vector<glm::vec2> textureCoordinates;
		std::vector<glm::vec3> normalCoordinates;
		std::vector<glm::vec3> vertexCoordinates;

		std::vector<unsigned int> vertexIndices;
		std::vector<unsigned int> normalIndices;
		std::vector<unsigned int> textureIndices;

		Loader::LoadObj(path, vertexCoordinates, textureCoordinates, normalCoordinates, vertexIndices, textureIndices, normalIndices,false);

		BufferLayout layout({ {ShaderDataType::Float3,"position"} });

		if (!textureIndices.empty())
			layout += {ShaderDataType::Float2, "texture"};
		if (!normalIndices.empty())
			layout += {ShaderDataType::Float3, "normals"};

		uint8_t offset = layout.GetStride() / sizeof(float);

		float* vertex = new float[offset];
		uint8_t localOffset = 0;
		WB_CORE_TIMER_START();
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
				glm::vec2 normalCoord = normalCoordinates[normalIndices[i]];
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
		WB_CORE_TIMER_END();
		WB_CORE_TRACE("File {0}: Processing time {1} milliseconds", path, WB_CORE_TIMER_END_MINUS_START(milliseconds));
		WB_CORE_TRACE("File {0}: Face count {1}", path, Indicies.size() / offset);
		WB_CORE_TRACE("File {0}: Vertex count without processing {1}", path, Indicies.size() * offset);
		WB_CORE_TRACE("File {0}: Postprocessing vertex count {1}", path, Vertex.size() / offset);
		m_VertexArray->AddVertexBuffer(&Vertex[0], Vertex.size() * sizeof(float),layout);
		m_VertexArray->SetIndexBuffer(&Indicies[0], Indicies.size());
	}
	

}
