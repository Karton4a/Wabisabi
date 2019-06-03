#include "wbpch.h"
#include "Log.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Wabisabi
{
	bool Log::s_Inited = false;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;
	void Log::Init()
	{
		if (!s_Inited)
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_CoreLogger = spdlog::stdout_color_mt("WABISABI");
			s_CoreLogger->set_level(spdlog::level::trace);

			s_AppLogger = spdlog::stdout_color_mt("APP");
			s_AppLogger->set_level(spdlog::level::trace);
			s_Inited = true;
		}
	}
}
