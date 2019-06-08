#include "wbpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"
#include <glad/glad.h>

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
		float vertex[6] = {
			.5f,.5f,
			.0f,.0f,
			.5f,.0f,
		};
		//VertexBuffer vb(vertex, 6 * sizeof(float));
		
	}
	Application::~Application()
	{
		//delete m_Window;
	}
	void Application::Run()
	{
		while (m_Running)
		{	
			glClearColor(1.f,1.f,.0f,1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			for (auto el : m_LayerStack)
			{
				el->OnUpdate();
			}
			m_Window->OnUpdate();	
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
		disp.Dispatch<WindowClose>(BIND_FN(OnWindowClose));
		disp.Dispatch<WindowResize>(BIND_FN(OnWindowResize));
		for (auto it = m_LayerStack.rbegin(); it !=m_LayerStack.rend() ; it++)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	bool Application::OnWindowClose(WindowClose& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResize& e)
	{
		//glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		return true;
	}
}