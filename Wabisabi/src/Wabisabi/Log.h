#pragma once
#include "wbpch.h"
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Wabisabi 
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		Log() {};
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
		static bool s_Inited;
	};
}

#define WB_CORE_TRACE(...)					::Wabisabi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WB_CORE_INFO(...)					::Wabisabi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WB_CORE_WARN(...)					::Wabisabi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WB_CORE_ERROR(...)					::Wabisabi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WB_CORE_FATAL(...)					::Wabisabi::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define WB_CORE_TIMER_INIT()				auto _time_start_ = std::chrono::high_resolution_clock::now();\
											auto _time_end_ = std::chrono::high_resolution_clock::now()

#define WB_CORE_TIMER_START()				_time_start_ = std::chrono::high_resolution_clock::now();
#define WB_CORE_TIMER_END()					_time_end_  = std::chrono::high_resolution_clock::now();
#define WB_CORE_TIMER_END_MINUS_START(...)	std::chrono::duration_cast<std::chrono::##__VA_ARGS__>(_time_end_ - _time_start_).count()

#define WB_TRACE(...)						::Wabisabi::Log::GetAppLogger()->trace(__VA_ARGS__)
#define WB_INFO(...)						::Wabisabi::Log::GetAppLogger()->info(__VA_ARGS__)
#define WB_WARN(...)						::Wabisabi::Log::GetAppLogger()->warn(__VA_ARGS__)
#define WB_ERROR(...)						::Wabisabi::Log::GetAppLogger()->error(__VA_ARGS__)
#define WB_FATAL(...)						::Wabisabi::Log::GetAppLogger()->fatal(__VA_ARGS__)

#define WB_TIMER_INIT()						auto _time_start_ = std::chrono::high_resolution_clock::now();\
											auto _time_end_ = std::chrono::high_resolution_clock::now()

#define WB_TIMER_START()					_time_start_ = std::chrono::high_resolution_clock::now()
#define WB_TIMER_END()						_time_end_ = std::chrono::high_resolution_clock::now()
#define WB_TIMER_END_MINUS_START(...)		std::chrono::duration_cast<std::chrono::##__VA_ARGS__>(_time_end_ - _time_start_).count()

#define WB_ASSERT(x, ...) { if(!(x)) { WB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define WB_CORE_ASSERT(x, ...) { if(!(x)) { WB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }