#include "wbpch.h"
#include "LayerStack.h"

namespace Wabisabi
{
	LayerStack::LayerStack()
		:m_LayerSeparator(m_Layers.begin())
	{}
	LayerStack::~LayerStack()
	{
		for (Layer* el : m_Layers)
			delete el;
		for (Layer* el : m_DisabledLayers)
			delete el;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerSeparator = m_Layers.emplace(m_LayerSeparator, layer);
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		LayerCollection::iterator it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerSeparator--;
			m_DisabledLayers.emplace_back(layer);
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		LayerCollection::iterator it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_DisabledLayers.emplace_back(overlay);
		}
	}
	void LayerStack::EnableLayer(Layer* layer)
	{
		LayerCollection::iterator it = std::find(m_DisabledLayers.begin(), m_DisabledLayers.end(), layer);
		if (it != m_DisabledLayers.end())
		{
			m_DisabledLayers.erase(it);
			PushLayer(layer);
		}
	}
	void LayerStack::EnableOverlay(Layer* overlay)
	{
		LayerCollection::iterator it = std::find(m_DisabledLayers.begin(), m_DisabledLayers.end(), overlay);
		if (it != m_DisabledLayers.end())
		{
			m_DisabledLayers.erase(it);
			PushOverlay(overlay);
		}
	}
}