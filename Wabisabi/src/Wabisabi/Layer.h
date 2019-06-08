#pragma once

#include "wbpch.h"
#include "Wabisabi/Events/Event.h"
#include "Core.h"

namespace Wabisabi
{
	class WABI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			:m_DebugName(name)
		{}
		virtual ~Layer() {};
		virtual void OnAttach(){}
		virtual void OnDettach(){}
		virtual void OnEvent(Event& e){}
		virtual void OnUpdate() {}
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}