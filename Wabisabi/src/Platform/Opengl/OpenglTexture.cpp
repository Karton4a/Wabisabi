#include "wbpch.h"
#include "OpenglTexture.h"
#include <glad/glad.h>
namespace Wabisabi
{
	OpenglTexture::OpenglTexture(const std::string& path)
	{
		LoadTexture(path);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_REPEAT, GL_CLAMP_TO_EDGE);//GL_TEXTURE_WRAP_S
		glTexParameteri(GL_TEXTURE_2D, GL_REPEAT, GL_CLAMP_TO_EDGE);// GL_TEXTURE_WRAP_T
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		DeleteData();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	OpenglTexture::~OpenglTexture()
	{
		glDeleteTextures(1, &m_RendererId);
	}
	void OpenglTexture::Bind(uint8_t slot) const
	{
		glBindTextureUnit(slot, m_RendererId);
		/*glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);*/
	}

	void OpenglTexture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}
