#pragma once
#include <glm/glm.hpp>

namespace Wabisabi
{
	using Float      =   float_t;
	using Float2     =   glm::vec2;
	using Float3     =   glm::vec3;
	using Float4     =   glm::vec4;
	using Int        =   int32_t;
	using Int2       =   glm::ivec2;
	using Int3       =   glm::ivec3;
	using Int4       =   glm::ivec4;
	using RGB        =   Float3;
	using RGBA       =   Float4;
	using RendererId =   uint32_t;
	using MaterialId =   int32_t;
}