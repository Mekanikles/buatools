#pragma once

#include <EASTL/functional.h>

#include <bua/core.h>

namespace bua
{
	struct RenderState;
}

struct SDL_Renderer;

int runSdlExample(const char* name, eastl::function<void(SDL_Renderer*, uint)> updateFunc);
void renderUIState(SDL_Renderer* renderer, const bua::RenderState& renderState);

struct DebugStats
{
	uint vertexCount;
	int indexCount;
};

void recordDebugStats(DebugStats& debugStats, const bua::RenderState& renderState);
void printDebugStats(const DebugStats& debugStats);
