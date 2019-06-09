#pragma once
#include "wbpch.h"

namespace Wabisabi
{
	class OpenglShader
	{
	public:

		OpenglShader(const std::string& vertexsrc, const std::string& fragmentsrc);
		~OpenglShader();
		void Bind() const;
		void UnBind() const;
	private:
		uint32_t m_RendererId;
	};
}