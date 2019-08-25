#pragma once
#include "wbpch.h"
#include "Wabisabi/Types.h"
#include "Wabisabi/Core.h"
namespace Wabisabi
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual int32_t GetLocation(const std::string& name) const = 0;
		virtual void SetUniform(const std::string& name, Int num) = 0;
		virtual void SetUniform(const std::string& name, Float num) = 0;
		virtual void SetUniform(const std::string& name, uint32_t num) = 0;
		virtual void SetUniform(const std::string& name, bool num) = 0;
		virtual void SetUniform(const std::string& name, Float num1, Float num2, Float num3, Float num4) = 0;
		virtual void SetUniform(const std::string& name, Float4 vec) = 0;
		virtual void SetUniform(const std::string& name, Float num1, Float num2, Float num3) = 0;
		virtual void SetUniform(const std::string& name, Float3 vec) = 0;
		virtual void SetUniform(const std::string& name, const glm::mat4& marix) = 0;
		static Ref<Shader> Create(const std::string& vertexsrc, const std::string& fragmentsrc);
	};
}