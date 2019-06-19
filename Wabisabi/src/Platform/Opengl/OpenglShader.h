#pragma once
#include "wbpch.h"
#include <glm/glm.hpp>
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
		void SetUniform1i(const std::string& name,int32_t num);
		void SetUniform4f(const std::string& name, float_t num1, float_t num2, float_t num3, float_t num4);
		void SetUniformMat4(const std::string& name,glm::mat4& marix);
	private:
		uint32_t m_RendererId;
	};
}