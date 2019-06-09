#include "Wabisabi.h"

class UserLayer : public Wabi::Layer
{
public:
	UserLayer()
		:Wabi::Layer("Examle")
	{

	}
	virtual void OnEvent(Wabi::Event& e) override
	{
		
	}
};


class Sandbox : public Wabi::Application
{
public:
	Sandbox()
	{
		//m_Window = std::shared_ptr<Wabi::Window>(Wabi::Window::Create());
		Wabi::Layer* overlay = new UserLayer();
		m_LayerStack.PushOverlay(overlay);
		
	}
	~Sandbox()
	{
			
	}
	void Init() override
	{
	}
	void Update() override
	{
		m_Window->OnUpdate();
	}
	void Draw() override
	{
		//printf("App Draw\n");
	}
private:
	
};


Wabi::Application* Wabi::CreateApplication()
{
	return new Sandbox();
}

void DeleteApplication(Wabi::Application* app)
{
	delete app;
}