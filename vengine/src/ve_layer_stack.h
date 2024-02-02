#pragma once
#include "ve_pch.h"
#include "common/ve_common.h"
#include "events/ve_event.h"


namespace VE {

class Layer;


class VE_API LayerStack {
   using Iterator = std::vector<Layer*>::iterator;
   using ReverseIterator = std::vector<Layer*>::reverse_iterator;

public:
   LayerStack() = default;
   virtual ~LayerStack();

   void PushLayer(Layer* layer);
   void PushOverlay(Layer* overlay);
   void PopLayer(Layer* layer);
   void PopOverlay(Layer* overlay);

   Iterator begin() { return layers.begin(); }
   Iterator end() { return layers.end(); }
   ReverseIterator rbegin() { return layers.rbegin(); }
   ReverseIterator rend() { return layers.rend(); }

private:
   std::vector<Layer*> layers{};
   unsigned int insertIndex = 0;
};
}