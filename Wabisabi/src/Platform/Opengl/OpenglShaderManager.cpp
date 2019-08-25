#include "wbpch.h"
#include "OpenglShaderManager.h"
namespace Wabisabi
{
	ShaderId OpenglShaderManager::GetShaderImpl(const BufferLayout& layout, const Material::Type materialType, int verison)
	{
		auto res = std::find_if(m_Shaders.begin(), m_Shaders.end(), 
			[&materialType, &layout](const ManagerElement& t) 
			{ 
				return t.MaterialType == materialType && t.Layout == layout; 
			});
		if (res != m_Shaders.end()) return std::distance(m_Shaders.begin(), res);

		std::stringstream vertexShader;
		vertexShader << "#version " << (verison != 0 ? verison : ShaderManager::s_DefaultShaderVersion) << std::endl;
		for (const auto& el : layout)
		{
			vertexShader << TypeToGLSL(el.Type) << " " << el.Name << std:: endl;
		}
		return 0;
	}
	std::string OpenglShaderManager::TypeToGLSL(ShaderDataType type)
	{
		switch (type)
		{
		case Wabisabi::ShaderDataType::None:	    return "";
		case Wabisabi::ShaderDataType::Float:	    return "float";
		case Wabisabi::ShaderDataType::Float2:	    return "vec2";
		case Wabisabi::ShaderDataType::Float3:	    return "vec3";
		case Wabisabi::ShaderDataType::Float4:	    return "vec4";
		case Wabisabi::ShaderDataType::Int:		    return "int";
		case Wabisabi::ShaderDataType::Int2:	    return "ivec2";
		case Wabisabi::ShaderDataType::Int3:	    return "ivec3";
		case Wabisabi::ShaderDataType::Int4:	    return "ivec4";
		case Wabisabi::ShaderDataType::Uint:	    return "uint";
		case Wabisabi::ShaderDataType::Uint2:	    return "uvec2";
		case Wabisabi::ShaderDataType::Uint3:	    return "uvec3";
		case Wabisabi::ShaderDataType::Uint4:	    return "uvec4";
		case Wabisabi::ShaderDataType::Float4x4:    return "mat4";
		case Wabisabi::ShaderDataType::Float3x3:    return "mat3";
		case Wabisabi::ShaderDataType::Float2x2:    return "mat2";
		default: return "";
		}
		return std::string();
	}
}
