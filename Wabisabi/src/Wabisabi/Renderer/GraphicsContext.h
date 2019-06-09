#pragma once
#include "wbpch.h"

namespace Wabisabi
{
	class GraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}