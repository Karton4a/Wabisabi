#pragma once
#include "wbpch.h"
#include <glm/glm.hpp>
#include "Wabisabi/Types.h"
#include "Wabisabi/Renderer/Shader.h"
namespace Wabisabi
{
	class OpenglShader : public Shader
	{
	public:
		OpenglShader(const std::string& vertexsrc, const std::string& fragmentsrc);
		virtual ~OpenglShader() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetUniform(const std::string& name, Int num) override;
		virtual void SetUniform(const std::string& name, Float num) override;
		virtual void SetUniform(const std::string& name, uint32_t num) override;
		virtual void SetUniform(const std::string& name, bool num) override;
		virtual void SetUniform(const std::string& name, Float num1, Float num2, Float num3, Float num4) override;
		virtual void SetUniform(const std::string& name, Float4 vec) override;
		virtual void SetUniform(const std::string& name, Float num1, Float num2, Float num3) override;
		virtual void SetUniform(const std::string& name, Float3 vec) override;
		virtual void SetUniform(const std::string& name,const glm::mat4& marix) override;
	private:
		int32_t GetLocation(const std::string& name) const;
	private:
		RendererId m_RendererId;
	};
}