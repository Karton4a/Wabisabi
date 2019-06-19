#pragma once


#ifndef NO_DLL_ENTRY_POINT

#include "Input.h"
#include "Log.h"
#include "Application.h"

//extern Wabi::Application* CreateApplication();
extern void DeleteApplication(Wabi::Application* app);

int main()
{
	Wabi::Log::Init();
	WB_CORE_INFO("Logger Init");
	auto app = Wabi::CreateApplication();
	
	Wabi::Application::Get().Run();
	
	DeleteApplication(app);
	delete Wabi::Input::Get();
	return 0;
}
	
#endif // !NO_DLL_ENTRY_POIN
