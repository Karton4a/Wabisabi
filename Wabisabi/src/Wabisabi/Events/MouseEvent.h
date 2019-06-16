#pragma once
#include "wbpch.h"
#include "Wabisabi/Core.h"
#include "Event.h"
namespace Wabisabi
{
	class WABI_API MouseButtonPressed : public Event
	{
	public:
		MouseButtonPressed(int button)
			:m_Button(button){}

		inline int GetButton() { return m_Button; }

		virtual std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: " << m_Button << std::endl;
			return ss.str();
		}
		SET_TYPE(MouseButtonPressed)
		SET_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
	private:
		int m_Button;
	};

	class WABI_API MouseButtonReleased : public Event
	{
	public:
		MouseButtonReleased(int button)
			:m_Button(button) {}

		inline int GetButton() { return m_Button; }

		virtual std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: " << m_Button << std::endl;
			return ss.str();
		}
		SET_TYPE(MouseButtonReleased)
		SET_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
	private:
		int m_Button;
	};

	class WABI_API MouseMoved : public Event
	{
	public:
		MouseMoved(double posx, double posy)
			:m_PosX(posx),m_PosY(posy) {}

		inline std::pair<double, double> GetPosition() { return {m_PosX,m_PosY}; }

		virtual std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: X =  "<< m_PosX <<" Y = "<< m_PosY << std::endl;
			return ss.str();
		}
		SET_TYPE(MouseMoved)
		SET_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double m_PosX,m_PosY;
	};

	class WABI_API MouseScrolled : public Event
	{
	public:
		MouseScrolled(double xoffset, double yoffset)
			:m_OffsetX(xoffset), m_OffsetY(yoffset) {}

		inline std::pair<double, double> GetPosition() { return { m_OffsetX,m_OffsetY }; }

		virtual std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event: X =  " << m_OffsetX << " Y = " << m_OffsetY << std::endl;
			return ss.str();
		}
		SET_TYPE(MouseScrolled)
		SET_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double m_OffsetX, m_OffsetY;
	};
}