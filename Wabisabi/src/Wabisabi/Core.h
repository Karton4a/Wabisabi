#pragma once
#include <memory>
#define Wabi Wabisabi

#define Wb Wabisabi

#ifndef WB_STATIC_LINK

	#ifdef WB_BUILD_DLL
		#define WABI_API _declspec(dllexport)
	#else
		#define WABI_API _declspec(dllimport)
	#endif 

#else
	#define WABI_API
#endif

namespace Wabisabi
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using WeakRef = std::weak_ptr<T>;
}