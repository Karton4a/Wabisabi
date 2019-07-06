#pragma once
#include "wbpch.h"
#include "Wabisabi/Log.h"
namespace Wabisabi
{
	enum class ShaderDataType
	{
		None = 0,Float,Float2,Float3,Float4,Int,Int2,Int3,Int4,Uint,Uint2,Uint3,Uint4
	};

	static uint16_t GetTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Wabisabi::ShaderDataType::None:   WB_CORE_ASSERT(false,"Unsuported Type None") return 0;

		case Wabisabi::ShaderDataType::Float:  return sizeof(float);
		case Wabisabi::ShaderDataType::Float2: return 2*sizeof(float);
		case Wabisabi::ShaderDataType::Float3: return 3*sizeof(float);
		case Wabisabi::ShaderDataType::Float4: return 4*sizeof(float);
		case Wabisabi::ShaderDataType::Int:    return sizeof(float);
		case Wabisabi::ShaderDataType::Int2:   return 2*sizeof(float);
		case Wabisabi::ShaderDataType::Int3:   return 3*sizeof(float);
		case Wabisabi::ShaderDataType::Int4:   return 4*sizeof(float);
		case Wabisabi::ShaderDataType::Uint:   return sizeof(float);
		case Wabisabi::ShaderDataType::Uint2:  return 2*sizeof(float);
		case Wabisabi::ShaderDataType::Uint3:  return 3*sizeof(float);
		case Wabisabi::ShaderDataType::Uint4:  return 4*sizeof(float);
		}
		return 0;
	}
	static uint16_t GetTypeCount(ShaderDataType type)
	{
		switch (type)
		{
		case Wabisabi::ShaderDataType::None:   WB_CORE_ASSERT(false, "Unsuported Type None") return 0;

		case Wabisabi::ShaderDataType::Float:  return 1;
		case Wabisabi::ShaderDataType::Float2: return 2;
		case Wabisabi::ShaderDataType::Float3: return 3;
		case Wabisabi::ShaderDataType::Float4: return 4;
		case Wabisabi::ShaderDataType::Int:    return 1;
		case Wabisabi::ShaderDataType::Int2:   return 2;
		case Wabisabi::ShaderDataType::Int3:   return 3;
		case Wabisabi::ShaderDataType::Int4:   return 4;
		case Wabisabi::ShaderDataType::Uint:   return 1;
		case Wabisabi::ShaderDataType::Uint2:  return 2;
		case Wabisabi::ShaderDataType::Uint3:  return 3;
		case Wabisabi::ShaderDataType::Uint4:  return 4;
		}
		return 0;
	}

	struct LayoutElement
	{
		std::string Name;
		uint32_t Size;
		uint32_t Count;
		uint32_t Offset;
		ShaderDataType Type;
		bool Normalized;
		LayoutElement()
			:Type(ShaderDataType::None), Name(""), Size(0), Count(0), Offset(0), Normalized(false) {}
		LayoutElement(ShaderDataType type,const std::string& name,bool normalized = false)
			:Type(type),Name(name),Size(GetTypeSize(type)),Count(GetTypeCount(type)),Offset(0),Normalized(normalized) {}
	};
	class BufferLayout
	{
	public:
		BufferLayout()
			:m_Stride(0)
		{}
		BufferLayout(const std::initializer_list<LayoutElement>& list)
			:m_Stride(0)
		{
			m_Layout = list;
			uint32_t offset = 0;
			for (LayoutElement& el : m_Layout)
			{
				el.Offset = offset;
				offset += el.Size;
				m_Stride += el.Size;
			}
		}
		const LayoutElement& operator +=(const LayoutElement& el)
		{
			if (m_Layout.empty())
			{
				m_Layout.push_back(el);
				m_Stride += el.Size;
			}
			else
			{
				m_Layout.push_back(el);
				size_t last = m_Layout.size() - 1;
				m_Layout[last].Offset = m_Layout[last - 1].Offset + m_Layout[last - 1].Size;
				m_Stride += m_Layout[last].Size;
			}
			return el;
		}
		inline const std::vector<LayoutElement>& GetLayout() const  { return m_Layout; }
		inline const uint32_t& GetStride() const { return m_Stride; }

		std::vector<LayoutElement>::iterator begin() { return m_Layout.begin(); }
		std::vector<LayoutElement>::iterator end() { return m_Layout.end(); }

		std::vector<LayoutElement>::const_iterator begin() const { return m_Layout.cbegin(); }
		std::vector<LayoutElement>::const_iterator end() const { return m_Layout.cend(); }

	private:
		uint32_t m_Stride;
		std::vector<LayoutElement> m_Layout;
	};
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Reset(const void* data, uint32_t size) const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static VertexBuffer* Create(const void* data,uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		inline virtual uint32_t GetCount() const = 0;
		virtual void Reset(const uint32_t* data, uint32_t count) const = 0;
		static IndexBuffer* Create(const uint32_t* data, uint32_t count);

	};
}
