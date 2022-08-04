// Must be included before eastl due to a re-definition of char8_t in eastl
#include <fmt/format.h>

#include <bua/elements/fill.h>
#include "sdlshared.h"

using namespace bua;

Context s_uiContext;

////////////////////////////////////////////////////////////////////////////////

template<typename ElementT>
ElementT* addElement(eastl::unique_ptr<ElementT> element)
{
	auto* retval = element.get();
	s_uiContext.elements.push_back(eastl::move(element));
	return retval;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
	eastl::array<elements::Fill*, 4> fills =
		{
			// TODO: Elements should not accept layout rects directly
			addElement(eastl::make_unique<elements::Fill>(Rect{100, 100, 50, 50}, Color{1, 1, 1, 1})),
			addElement(eastl::make_unique<elements::Fill>(Rect{200, 100, 50, 50}, Color{1, 1, 0, 1})),
			addElement(eastl::make_unique<elements::Fill>(Rect{100, 200, 50, 50}, Color{0, 1, 1, 1})),
			addElement(eastl::make_unique<elements::Fill>(Rect{200, 200, 50, 50}, Color{1, 0, 1, 1})),
		};

	bua::RenderState uiRenderState(10000);

	DebugStats debugStats;
	uint lastFrameDebugTick = 0;

	return runSdlExample("SDL2 retained example", [&](SDL_Renderer* renderer, uint currentFrameTick)
		{
			// Animate color
			{
				const float progress = (currentFrameTick % 500) / 500.0f;
				Color color{1, 1, 1, progress};

				fills[0]->update(Rect{100, 100, 50, 50}, color);
			}

			uiRenderState.reset();
			for (auto& element : s_uiContext.elements)
				element->render(&uiRenderState);

			renderUIState(renderer, uiRenderState);

			recordDebugStats(debugStats, uiRenderState);
			if (currentFrameTick - lastFrameDebugTick > 1000)
			{
				printDebugStats(debugStats);
				lastFrameDebugTick = currentFrameTick;
			}			
		});
}

////////////////////////////////////////////////////////////////////////////////
