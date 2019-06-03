#pragma once

#define Wabi Wabisabi

#define Wb Wabisabi
#ifndef WB_BUILD_STATIC

	#ifdef WB_BUILD_DLL
		#define WABI_API //_declspec(dllexport)
	#else
		#define WABI_API //_declspec(dllimport)
	#endif 

#else
	#define WABI_API
#endif