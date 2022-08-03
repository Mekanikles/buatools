// Must be included before eastl due to a re-definition of char8_t in eastl
#include <fmt/format.h>

#include "sdlshared.h"

#include <EASTL/fixed_vector.h>
#include <SDL2/SDL.h>
#include <bua/bua.h>

////////////////////////////////////////////////////////////////////////////////

int runSdlExample(const char* name, eastl::function<void(SDL_Renderer*, uint)> updateFunc)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fmt::print(stderr, "Could not initialize sdl2: {}\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN
		);

	if (window == NULL) {
		fmt::print(stderr, "Could not create window: {}\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int done = false;
	SDL_Event event;

	uint lastFrameTick = 0;
	while (!done) {
		uint currentFrameTick = SDL_GetTicks();
		if (currentFrameTick - lastFrameTick < (1000 / 60))
			continue;

		lastFrameTick = currentFrameTick;

		// Frame
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT) 
					done = true;

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
			}

			// Clear window to black
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			updateFunc(renderer, currentFrameTick);

			SDL_RenderPresent(renderer);
		}
	}
	SDL_Quit();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void renderUIState(SDL_Renderer* renderer, const bua::RenderState& renderState)
{
	using namespace bua;

	static eastl::vector<SDL_Vertex> s_vertices;
	static eastl::vector<int> s_indices;

	const auto& meshData = renderState.meshData;
	const auto numvertices = meshData.vertexData.size();
	const auto numindices = meshData.indexData.size();

	// TODO: It would be nice to allow for custom renderwriters to avoid this conversion
	s_vertices.clear();
	s_vertices.reserve(numvertices);
	s_indices.clear();
	s_indices.reserve(numindices);

	for (const bua::MeshData::Vertex& inv : meshData.vertexData)
	{
		auto& outv = s_vertices.push_back();

		outv.position.x = inv.x;
		outv.position.y = inv.y;
		outv.color.r = Uint8(255 * inv.color.r);
		outv.color.g = Uint8(255 * inv.color.g);
		outv.color.b = Uint8(255 * inv.color.b);
		outv.color.a = Uint8(255 * inv.color.a);
	}

	for (auto& ini : meshData.indexData)
	{
		s_indices.push_back(ini);
	}
	
	SDL_RenderGeometry(renderer, nullptr, s_vertices.data(), s_vertices.size(), s_indices.data(), s_indices.size());
}

////////////////////////////////////////////////////////////////////////////////

void recordDebugStats(DebugStats& debugStats, const bua::RenderState& renderState)
{
	debugStats.vertexCount = renderState.meshData.vertexData.size();
	debugStats.indexCount = renderState.meshData.indexData.size();
}

////////////////////////////////////////////////////////////////////////////////

void printDebugStats(const DebugStats& debugStats)
{
	fmt::print(stderr, "Vertices: {}, Indices: {}\n", debugStats.vertexCount, debugStats.indexCount);
}

////////////////////////////////////////////////////////////////////////////////
