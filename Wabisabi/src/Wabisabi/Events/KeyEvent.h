#pragma once
#include "wbpch.h"
#include "Wabisabi/Core.h"
#include "Event.h"
namespace Wabisabi
{
	class WABI_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; };
		SET_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode)
		{}
		int m_KeyCode;
	};

	class WABI_API KeyPressed : public KeyEvent
	{
	public:
		KeyPressed(int keycode, unsigned int repeat)
			:KeyEvent(keycode), m_RepeatCount(repeat)
		{};
		inline unsigned int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override  final
		{
			std::stringstream ss;
			ss << GetName() << "Event:" << m_KeyCode << " " << m_RepeatCount << " repats" << std::endl;
			return ss.str();
		}
		SET_TYPE(KeyPressed)
	private:
		unsigned int m_RepeatCount;
	};

	class WABI_API KeyReleased : public KeyEvent
	{
	public:

		KeyReleased(unsigned int keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName() << "Event:" << m_KeyCode << std::endl;
			return ss.str();
		}
		SET_TYPE(KeyReleased)
	};
	class WABI_API KeyTyped : public KeyEvent
	{
	public:

		KeyTyped(int keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override final
		{
			std::stringstream ss;
			ss << GetName()<<"Event:"<< m_KeyCode << std::endl;
			return ss.str();
		}
		SET_TYPE(KeyTyped)
	};
}