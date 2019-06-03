#pragma once
#include "wbpch.h"
#include "Wabisabi/Core.h"
namespace Wabisabi
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4,
		EventCategoryWindow = 1 << 5,
	};
#define SET_TYPE(type) static EventType GetStaticType(){ return EventType::##type; }\
					   virtual EventType GetType() const override final { return GetStaticType();}\
					   virtual const char* GetName() const override final {return #type;}
#define SET_CATEGORY(x) virtual int GetCategory() const override final { return x;}
	class WABI_API Event
	{
	public:
		bool Handled = false;
		Event() {}
		virtual ~Event() {};
		virtual EventType GetType() const = 0;
		virtual int GetCategory() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const{ return GetName(); };
		bool IsInCategory(EventCategory category)
		{
			return GetCategory() & category;
		}

	};
	class WABI_API EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			:m_Event(e) {};

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled = func(*((T*)&m_Event));
				return true;
			}
			return false;
		};
	private:
		Event& m_Event;
	};
}
