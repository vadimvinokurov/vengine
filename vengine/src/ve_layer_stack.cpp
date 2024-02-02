#include "ve_pch.h"
#include "ve_layer_stack.h"
#include "ve_layer.h"
#include "common/ve_assert.h"


VE::LayerStack::~LayerStack()
{
   for (Layer* layer : layers) {
      layer->OnDetach();
      delete layer;
   }
}


void VE::LayerStack::PushLayer(Layer* layer)
{
   layers.emplace(layers.begin() + insertIndex, layer);
   ++insertIndex;

   layer->OnAttach();
}


void VE::LayerStack::PushOverlay(Layer* overlay)
{
   layers.emplace_back(overlay);
   overlay->OnAttach();
}


void VE::LayerStack::PopLayer(Layer* layer)
{
   auto it = std::ranges::find(layers, layer);
   if (it == layers.end()) {
      ASSERT_FAILED("Can't find layer '%s'", layer->GetName());
      return;
   }
   ASSERT_MSG(std::distance(layers.begin(), it) < insertIndex, "It is overlay layer");

   layers.erase(it);
   --insertIndex;

   layer->OnDetach();
}


void VE::LayerStack::PopOverlay(Layer* overlay)
{
   auto it = std::ranges::find(layers, overlay);
   if (it == layers.end()) {
      ASSERT_FAILED("Can't find layer '%s'", overlay->GetName());
      return;
   }
   ASSERT_MSG(std::distance(layers.begin(), it) >= insertIndex, "It is not overlay layer");

   layers.erase(it);

   overlay->OnDetach();
}