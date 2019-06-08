#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "LayerStack.h"
namespace Wabi {

	class WABI_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run() ;
		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual void OnEvent(Event& e);
		inline static Application& Get() { return *s_Instance; };
		inline const Window& GetWindow() const { return *m_Window;};
		virtual bool OnWindowClose(WindowClose& e);
		virtual bool OnWindowResize(WindowResize& e);
	protected:
		std::shared_ptr<Window> m_Window;
		//Window* m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

