#pragma once
#include "wbpch.h"
#include "Wabisabi/Core.h"
#include "Event.h"
namespace Wabisabi
{
	class WABI_API WindowResize :public Event
	{
	public:
		WindowResize(unsigned int width,unsigned int height)
			:m_Width(width),m_Height(height)
		{}
		inline std::pair<unsigned int, unsigned int>GetSize() const { return{ m_Width ,m_Height }; }
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: " << m_Width << ", " << m_Height << std::endl;
			return ss.str();
		}
		SET_TYPE(WindowResize)
		SET_CATEGORY(EventCategoryWindow)
	private:
		int m_Width, m_Height;
	};
	class WABI_API WindowClose :public Event
	{
	public:
		WindowClose(){}
		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: "<<std::endl;
			return ss.str();
		}
		SET_TYPE(WindowClose)
		SET_CATEGORY(EventCategoryWindow)
	};
	class WABI_API WindowFocus :public Event
	{
	public:
		WindowFocus() {}
		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: " << std::endl;
			return ss.str();
		}
		SET_TYPE(WindowFocus)
		SET_CATEGORY(EventCategoryWindow)
	};
	class WABI_API WindowLostFocus :public Event
	{
	public:
		WindowLostFocus() {}
		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: " << std::endl;
			return ss.str();
		}
		SET_TYPE(WindowLostFocus)
		SET_CATEGORY(EventCategoryWindow)
	};
	
	class WABI_API WindowMoved :public Event
	{
	public:
		WindowMoved(unsigned int xpos, unsigned int ypos)
			:m_PosX(xpos), m_PosY(ypos)
		{}
		inline std::pair<unsigned int, unsigned int> GetPosition() const { return{ m_PosX ,m_PosY }; }
		inline unsigned int GetWidth() const { return m_PosX; }
		inline unsigned int GetHeight() const { return m_PosY; }
		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: X =" << m_PosX << ",Y = " << m_PosY << std::endl;
			return ss.str();
		}
		SET_TYPE(WindowMoved)
		SET_CATEGORY(EventCategoryWindow)
	private:
		int m_PosX, m_PosY;
	};
}