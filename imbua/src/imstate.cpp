#include "imstate.h"

namespace bua
{

eastl::unique_ptr<ImState> g_currentImState;

void ImState::onBeginRender()
{
	// Reset all id counters
	for (auto& kvp : typeMap)
	{
		kvp.second.idCounter = 0;
	}
}


}