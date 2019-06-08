#pragma once
#include "wbpch.h"
#include "Layer.h"


namespace Wabisabi
{
	typedef std::vector<Layer*> LayerCollection;
	class LayerStack
	{
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void EnableLayer(Layer* layer);
		void EnableOverlay(Layer* overlay);
		
		LayerCollection::iterator begin() { return m_Layers.begin(); }
		LayerCollection::iterator end() { return m_Layers.begin(); }
		LayerCollection::reverse_iterator rbegin(){ return m_Layers.rbegin(); }
		LayerCollection::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		LayerCollection m_Layers;
		LayerCollection m_DisabledLayers;
		LayerCollection::iterator m_LayerSeparator;
	};
}