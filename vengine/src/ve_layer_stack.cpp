#include "ve_pch.h"
#include "ve_layer_stack.h"
#include "ve_layer.h"
#include "common/ve_assert.h"


VE::LayerStack::~LayerStack()
{
   for (Layer* layer : layers) {
      delete layer;
   }
}


void VE::LayerStack::PushLayer(Layer* layer)
{
   layers.emplace(layers.begin() + insertIndex, layer);
   ++insertIndex;
}


void VE::LayerStack::PushOverlay(Layer* overlay)
{
   layers.emplace_back(overlay);
}


void VE::LayerStack::PopLayer(Layer* layer)
{
   auto it = std::ranges::find(layers, layer);
   if (it == layers.end()) {
      return;
   }
   ASSERT_MSG(std::distance(layers.begin(), it) < insertIndex, "It is overlay layer");

   layers.erase(it);
   --insertIndex;
}


void VE::LayerStack::PopOverlay(Layer* overlay)
{
   auto it = std::ranges::find(layers, overlay);
   if (it == layers.end()) {
      return;
   }
   ASSERT_MSG(std::distance(layers.begin(), it) >= insertIndex, "It is not overlay layer");

   layers.erase(it);
}