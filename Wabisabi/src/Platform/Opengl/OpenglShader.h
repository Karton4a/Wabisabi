#pragma once
#include "wbpch.h"
#include <glm/glm.hpp>
#include "Wabisabi/Types.h"
namespace Wabisabi
{
	class OpenglShader
	{
	public:
		OpenglShader(const std::string& vertexsrc, const std::string& fragmentsrc);
		~OpenglShader();
		void Bind() const;
		void UnBind() const;
		int32_t GetLocation(const std::string& name) const;
		void SetUniform(const std::string& name, Int num);
		void SetUniform(const std::string& name, Float num);
		void SetUniform(const std::string& name, uint32_t num);
		void SetUniform(const std::string& name, bool num);
		void SetUniform(const std::string& name, Float num1, Float num2, Float num3, Float num4);
		void SetUniform(const std::string& name, Float4 vec);
		void SetUniform(const std::string& name, Float num1, Float num2, Float num3);
		void SetUniform(const std::string& name, Float3 vec);
		void SetUniform(const std::string& name,const glm::mat4& marix);
	private:

		RendererId m_RendererId;
	};
}