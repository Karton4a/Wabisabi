#pragma once
#include "Wabisabi/Renderer/ShaderManager.h"
namespace Wabisabi
{
	class OpenglShaderManager final : public ShaderManager
	{
	public:
		OpenglShaderManager() = default;
		~OpenglShaderManager() = default;
		virtual ShaderId GetShaderImpl(const BufferLayout& layout, const Material::Type materialType, int verison = 0) override;
	private:
		std::string TypeToGLSL(ShaderDataType type);
	private:
		struct ManagerElement
		{
			Material::Type MaterialType = Material::None;
			BufferLayout Layout;
			OpenglShader Shader;
			struct Uniform {
				LayoutElement Element;
				std::string name;
			};
			std::vector<Uniform> Uniforms;
		};
		std::vector <ManagerElement> m_Shaders;
	};
}