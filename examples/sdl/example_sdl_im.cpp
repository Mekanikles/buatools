// Must be included before eastl due to a re-definition of char8_t in eastl
#include <fmt/format.h>

#include <bua/imbua.h>
#include "sdlshared.h"

using namespace bua;

////////////////////////////////////////////////////////////////////////////////

void drawUI(not_null<bua::RenderState*> renderState, uint currentFrameTick)
{
	im::beginRender();

	// Animate color
	const float progress = (currentFrameTick % 500) / 500.0f;
	Color color{1, 1, 1, progress};

	// TODO: Elements should not accept layout rects like this
	im::fill(Rect{100, 100, 50, 50}, Color{1, 0, 1, 1});
	im::fill(Rect{200, 100, 50, 50}, Color{0, 1, 1, 1});
	im::fill(Rect{100, 200, 50, 50}, Color{1, 1, 0, 1});
	im::fill(Rect{200, 200, 50, 50}, color);

	renderState->reset();
	bua::im::endRender(renderState);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
	bua::RenderState uiRenderState(10000);
	DebugStats debugStats;
	uint lastFrameDebugTick = 0;

	return runSdlExample("SDL2 IM example", [&](SDL_Renderer* renderer, uint currentFrameTick)
		{
			drawUI(&uiRenderState, currentFrameTick);
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
