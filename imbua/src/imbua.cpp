#include <bua/imbua.h>

#include "imstate.h"

namespace bua
{

////////////////////////////////////////////////////////////////////////////////

void im::beginRender()
{
	if (!g_currentImState)
		g_currentImState = eastl::make_unique<ImState>();

	g_currentImState->onBeginRender();
}

////////////////////////////////////////////////////////////////////////////////

void im::endRender(not_null<RenderState*> renderState)
{
	Context& context = g_currentImState->context;

	for (auto& element : context.elements)
		element->render(renderState);
}

////////////////////////////////////////////////////////////////////////////////

}
