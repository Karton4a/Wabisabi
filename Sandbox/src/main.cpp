
#include "Wabisabi.h"

class Sandbox : public Wabi::Application
{
public:
	Sandbox()
	{
		//m_Window = std::shared_ptr<Wabi::Window>(Wabi::Window::Create());
	}
	~Sandbox()
	{
		
	}

	void Init() override
	{
		printf("App Init\n");
	}
	void Update() override
	{
		m_Window->OnUpdate();
	}
	void Draw() override
	{
		printf("App Draw\n");
	}
};


Wabi::Application* CreateApplication()
{
	return new Sandbox();
}

void DeleteApplication(Wabi::Application* app)
{
	delete app;
}