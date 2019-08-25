#pragma once
#include "Material.h"
#include "Wabisabi/Renderer/Buffer.h"

namespace Wabisabi
{
	constexpr auto VERTEX_POSITION_NAME  =   "u_position";
	constexpr auto VERTEX_TEXTURE_NAME   =   "u_texture";
	constexpr auto VERTEX_NORMAL_NAME    =   "u_normal";

	using ShaderId = int32_t;
	class ShaderManager
	{
	public:
		static void Create();
		static void Delete();
		virtual ~ShaderManager() = default;
		static ShaderId& GetShader(const BufferLayout& layout, const Material::Type materialType, int verison = 0) { s_Instance->GetShaderImpl(layout, materialType, verison); };
	protected:
		ShaderManager() = default;
		virtual ShaderId GetShaderImpl(const BufferLayout& layout ,const Material::Type materialType,int verison = 0) = 0;
		static int s_DefaultShaderVersion;
	private:
		static ShaderManager* s_Instance;
	};
}
