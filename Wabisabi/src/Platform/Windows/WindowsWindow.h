#pragma once
#include"wbpch.h"
#include "Wabisabi/Window.h"
#include <GLFW/glfw3.h>

namespace Wabisabi
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() final;
		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		void SetVSync(bool enabled = true) override;
		bool isVSync() const override;
		virtual void SetCallback(std::function<void(Event&)> fn) override final { m_Data.Callback = fn; };
		void* GetNativeWindow() const override;
	private:
		void Init(const WindowProps& props);
		void Destroy();

	private:

		GLFWwindow* m_Window;

		struct WindowData
		{
			using CallbackFn = std::function<void(Event&)>;
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			CallbackFn Callback;
		};

		WindowData m_Data;
	public:
		static unsigned int s_objCount; //TODO сделать что то поумнее
	
	};
	unsigned int WindowsWindow::s_objCount = 0;
}