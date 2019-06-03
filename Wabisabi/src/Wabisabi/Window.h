#pragma once
#include "wbpch.h"
#include "Core.h"
#include "Events/Event.h"
namespace Wabi
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		WindowProps(const std::string& title = "Wabisabi Engine",unsigned int width = 1280, unsigned int height = 720)
			:Title(title),Width(width),Height(height)
		{}
	};

	class WABI_API Window
	{
	public:
		virtual ~Window() {}; 

		virtual void OnUpdate() = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual void SetVSync(bool enabled = true) = 0;
		virtual bool isVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void SetCallback(std::function<void(Event&)> fn) = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}
