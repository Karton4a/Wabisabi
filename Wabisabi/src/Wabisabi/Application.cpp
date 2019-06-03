#include "wbpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"
namespace Wabi {
	Application* Application::s_Instance = nullptr;
#define BIND_FN(x) std::bind(&Application::##x, this, std::placeholders::_1)
	Application::Application()
	{
		if (s_Instance != nullptr)
		{
			//TODO Assert or just change s_Instance on new object
			WB_CORE_ERROR("App object already exist");
			__debugbreak();
		}
		s_Instance = this;
		m_Window = std::shared_ptr<Wabi::Window>(Wabi::Window::Create());
		m_Running = true;
		m_Window->SetCallback(BIND_FN(OnEvent));
	}
	Application::~Application()
	{
		//delete m_Window;
	}
	void Application::Run()
	{
		while (m_Running)
		{	
			Update();
			//m_Window->OnUpdate();	
		}
		
	}
	void Application::Init()
	{
		printf("Base Init\n");
	}
	void Application::Update()
	{
		printf("Base Update\n");
	}
	void Application::Draw()
	{
		printf("Base Draw\n");
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher disp(e);
		disp.Dispatch<WindowClose>(BIND_FN(OnWindowsClose));
	}
	bool Application::OnWindowsClose(WindowClose& e)
	{
		m_Running = false;
		return true;
	}
}