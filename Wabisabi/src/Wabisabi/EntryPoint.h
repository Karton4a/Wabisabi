#pragma once


#ifndef NO_DLL_ENTRY_POINT
#include "Input.h"
#include "Log.h"
extern Wabi::Application* CreateApplication();
extern void DeleteApplication(Wabi::Application* app);

int main()
{
	Wabi::Log::Init();
	WB_CORE_WARN("Logger Init");
	auto app = CreateApplication();
	
	Wabi::Application::Get().Run();
	
	DeleteApplication(app);
	delete Wabi::Input::Get();
	return 0;
}
	
#endif // !NO_DLL_ENTRY_POINT
