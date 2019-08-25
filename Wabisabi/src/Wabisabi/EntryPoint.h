#pragma once


#ifndef NO_DLL_ENTRY_POINT

#include "Input.h"
#include "Log.h"
#include "Application.h"
#include "Wabisabi/Renderer/ShaderManager.h"
//extern Wabi::Application* CreateApplication();
extern void DeleteApplication(Wabi::Application* app);


int main()
{
	Wabi::Log::Init();
	Wabi::ShaderManager::Create();
	WB_CORE_INFO("Logger Init");


	auto app = Wabi::CreateApplication();
	Wabi::Application::Get().Run();
	
	DeleteApplication(app);
	delete Wabi::Input::Get();
	Wabi::ShaderManager::Delete();
	return 0;
}
	
#endif // !NO_DLL_ENTRY_POIN
