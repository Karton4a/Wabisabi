#pragma once
#include "wbpch.h"
namespace Wabisabi
{
	class Texture
	{
	public:
		virtual ~Texture() {};
		void LoadTexture(const std::string& path);
		void DeleteData();
		virtual void Bind(uint8_t slot = 0) const = 0;
		virtual void UnBind() const = 0;
		static Texture* Create(const std::string& path);
	protected:
		char* m_Data;
		uint32_t m_Width;
		uint32_t m_Height;
		uint8_t m_BPP;
	};
}