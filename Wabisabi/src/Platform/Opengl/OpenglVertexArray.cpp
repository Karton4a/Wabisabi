#include "wbpch.h"
#include "OpenglVertexArray.h"
#include <glad/glad.h>
namespace Wabisabi
{
	static GLint ShaderTypeToOpengl(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:	      return GL_FLOAT;
			case ShaderDataType::Float2:      return GL_FLOAT;
			case ShaderDataType::Float3:      return GL_FLOAT;
			case ShaderDataType::Float4:      return GL_FLOAT;
			case ShaderDataType::Int:         return GL_INT;
			case ShaderDataType::Int2:        return GL_INT;
			case ShaderDataType::Int3:        return GL_INT;
			case ShaderDataType::Int4:        return GL_INT;
			case ShaderDataType::Uint:        return GL_UNSIGNED_INT;
			case ShaderDataType::Uint2:       return GL_UNSIGNED_INT;
			case ShaderDataType::Uint3:       return GL_UNSIGNED_INT;
			case ShaderDataType::Uint4:       return GL_UNSIGNED_INT;
		}
		return 0;
	}
	OpenglVertexArray::OpenglVertexArray()
		:m_LayoutLevels(0)
	{
		glCreateVertexArrays(1, &m_RendererId);

	}
	OpenglVertexArray::~OpenglVertexArray()
	{
		glDeleteVertexArrays(1,&m_RendererId);
	}
	void OpenglVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}
	void OpenglVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenglVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();
		const auto& layout = buffer->GetLayout();
		for (const auto& el : layout)
		{
			glEnableVertexAttribArray(m_LayoutLevels);
			glVertexAttribPointer(m_LayoutLevels, el.Count, ShaderTypeToOpengl(el.Type), el.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (GLvoid*)el.Offset);
			m_LayoutLevels++;
		}

		m_VertexBuffers.push_back(buffer);
	}
	void OpenglVertexArray::AddVertexBuffer(const void* data, size_t size, BufferLayout& layout)
	{
		std::shared_ptr<VertexBuffer> buffer(VertexBuffer::Create(data, size));
		buffer->SetLayout(layout);

		Bind();
		buffer->Bind();

		for (const auto& el : layout)
		{
			glEnableVertexAttribArray(m_LayoutLevels);
			glVertexAttribPointer(m_LayoutLevels, el.Count, ShaderTypeToOpengl(el.Type), el.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (GLvoid*)el.Offset);
			m_LayoutLevels++;
		}

		m_VertexBuffers.push_back(buffer);
	}
	void OpenglVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
	}
	void OpenglVertexArray::SetIndexBuffer(const uint32_t* data, uint32_t count)
	{
		m_IndexBuffer.reset(IndexBuffer::Create(data,count));
		Bind();
		m_IndexBuffer->Bind();
	}
}